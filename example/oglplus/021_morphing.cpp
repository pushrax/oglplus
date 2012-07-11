/**
 *  @example oglplus/021_morphing.cpp
 *  @brief Shows simple morphing animation
 *
 *  @image html 021_morphing.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <cstdlib>

#include "example.hpp"

namespace oglplus {

class PointVertShader
 : public VertexShader
{
public:
	PointVertShader(void)
	 : VertexShader(
		ObjectDesc("Vertex shader"),
		StrLit("#version 330\n"
		"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
		"uniform vec3 Color1, Color2;"
		"uniform float Status;"

		"in vec4 Position1, Position2;"
		"in float Radiance1, Radiance2;"

		"out vec3 vertColor;"

		"void main(void)"
		"{"
		"	gl_Position = "
		"		ProjectionMatrix * "
		"		CameraMatrix * "
		"		ModelMatrix * "
		"		mix(Position1, Position2, Status);"
		"	gl_PointSize = (2.0 + 3.0 * mix("
		"		Radiance1, "
		"		Radiance2, "
		"		Status"
		"	));"
		"	vertColor = mix("
		"		(0.2 + Radiance1) * Color1,"
		"		(0.2 + Radiance2) * Color2,"
		"		Status"
		"	);"
		"}")
	)
	{ }
};

class PointFragShader
 : public FragmentShader
{
public:
	PointFragShader(void)
	 : FragmentShader(
		ObjectDesc("Fragment shader"),
		StrLit("#version 330\n"

		"in vec3 vertColor;"
		"out vec3 fragColor;"

		"void main(void)"
		"{"
		"	fragColor = vertColor;"
		"}")
	)
	{ }
};

class PointProgram
 : public HardwiredTupleProgram<std::tuple<PointVertShader, PointFragShader> >
{
private:
	typedef HardwiredTupleProgram<std::tuple<PointVertShader, PointFragShader> >
		_base_program;
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> projection_matrix, camera_matrix, model_matrix;
	ProgramUniform<Vec3f> color_1, color_2;
	ProgramUniform<GLfloat> status;

	PointProgram(void)
	 : _base_program("Point program")
	 , projection_matrix(prog(), "ProjectionMatrix")
	 , camera_matrix(prog(), "CameraMatrix")
	 , model_matrix(prog(), "ModelMatrix")
	 , color_1(prog(), "Color1")
	 , color_2(prog(), "Color2")
	 , status(prog(), "Status")
	{ }
};

class Shape
{
protected:
	Context gl;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertex attributes
	Array<Buffer> vbos;

	const size_t point_count;

	void make_shape_1(const Program& prog, int vbo, const GLchar* name)
	{
		vbos[vbo].Bind(Buffer::Target::Array);

		std::vector<GLfloat> data(point_count * 3);
		auto i = data.begin(), e = data.end();
		while(i != e)
		{
			auto phi = FullCircles((std::rand() % 1001)*0.001);
			auto rho = RightAngles((std::rand() % 1001)*0.002-1.0);

			*i++ = Cos(phi) * Cos(rho);
			*i++ = Sin(rho);
			*i++ = Sin(phi) * Cos(rho);
		}

		Buffer::Data(Buffer::Target::Array, data);

		VertexAttribArray attr(prog, name);
		attr.Setup(3, DataType::Float);
		attr.Enable();
	}

	void make_shape_2(const Program& prog, int vbo, const GLchar* name)
	{
		vbos[vbo].Bind(Buffer::Target::Array);

		std::vector<GLfloat> data(point_count * 3);
		auto i = data.begin(), e = data.end();
		while(i != e)
		{
			auto phi = FullCircles((std::rand() % 1001)*0.001);
			auto rho = FullCircles((std::rand() % 1001)*0.001);

			*i++ = Cos(phi) * (0.5 + 0.5 * (1.0 + Cos(rho)));
			*i++ = Sin(rho) * 0.5;
			*i++ = Sin(phi) * (0.5 + 0.5 * (1.0 + Cos(rho)));
		}

		Buffer::Data(Buffer::Target::Array, data);

		VertexAttribArray attr(prog, name);
		attr.Setup(3, DataType::Float);
		attr.Enable();
	}

	void make_radiance(const Program& prog, int vbo, const GLchar* name)
	{
		vbos[vbo].Bind(Buffer::Target::Array);

		std::vector<GLfloat> data(point_count);
		for(auto i=data.begin(), e=data.end(); i!=e; ++i)
			*i = (std::rand() % 101) * 0.01;
		Buffer::Data(Buffer::Target::Array, data);

		VertexAttribArray attr(prog, name);
		attr.Setup(1, DataType::Float);
		attr.Enable();
	}
public:
	Shape(const Program& prog)
	 : vbos(4)
	 , point_count(4096)
	{
		// bind the VAO for the shape
		vao.Bind();

		make_shape_1(prog, 0, "Position1");
		make_shape_2(prog, 1, "Position2");
		make_radiance(prog, 2, "Radiance1");
		make_radiance(prog, 3, "Radiance2");
	}

	void Draw(void)
	{
		vao.Bind();
		gl.DrawArrays(PrimitiveType::Points, 0, point_count);
	}
};

class MorphingExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	PointProgram point_prog;

	Shape shape;

	double prev_time;
	double status;
public:
	MorphingExample(void)
	 : shape(point_prog)
	 , prev_time(0.0)
	 , status(0.0)
	{
		point_prog.color_1 = Vec3f(1.0, 0.5, 0.4);
		point_prog.color_2 = Vec3f(1.0, 0.8, 0.7);

		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::ProgramPointSize);
		gl.Enable(Capability::Blend);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		point_prog.projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		if(long(time) % 4 == 0)
		{
			status += (time - prev_time);
		}
		else if(status != double(long(status)))
		{
			if(status - double(long(status)) < 0.5)
				status = double(long(status));
			else status =1.0 + double(long(status));
		}
		prev_time = time;

		gl.Clear().ColorBuffer().DepthBuffer();

		point_prog.status = 0.5 - 0.5*CosineWave(status * 0.5);

		CamMatrixf camera = CamMatrixf::Orbiting(
			Vec3f(),
			4.5,
			FullCircles(time / 19.0),
			Degrees(45 + SineWave(time / 15.0) * 40)
		);
		point_prog.camera_matrix.Set(camera);

		point_prog.model_matrix.Set(
			ModelMatrixf::RotationX(RightAngles(status))
		);
		shape.Draw();
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new MorphingExample);
}

} // namespace oglplus
