/**
 *  @file oglplus/texgen/texture_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_TEXTURE_NODE_HPP
#define OGLPLUS_TEXGEN_TEXTURE_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/base_input.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/uniform.hpp>

namespace oglplus {
namespace texgen {

class TextureNode;

class TextureOutputSlot
 : public BaseOutputSlot
{
private:
	friend class TextureNode;

	FallbackInputSlot<GlobalCoordinateSlot, true> _coord;
protected:
	Texture _texture;
	TextureTarget _target;
	PixelDataFormat _format;
	UniformLoc _location;
public:
	TextureOutputSlot(
		Node& parent,
		Texture&&,
		TextureTarget,
		PixelDataFormat
	);

	void BindLocation(void);

	UniformLoc GetLocation(void) { return _location; }

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class TextureNode
 : public SingleBaseOutputNode
{
private:
	TextureOutputSlot _output;
protected:
	Texture& _tex(void) { return _output._texture; }
public:
	TextureNode(Texture&&, TextureTarget, PixelDataFormat);

	TextureNode& BindUniform(void)
	{
		_output.BindLocation();
		return *this;
	}

	TextureNode& SetSampler(TextureUnitSelector unit)
	{
		UniformSampler(_output.GetLocation()).Set(GLint(unit));
		return *this;
	}

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	BaseOutputSlot& SingleOutput(void)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/texture_node.ipp>
//#endif

#endif // include guard
