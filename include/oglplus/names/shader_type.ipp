/*
 *  .file oglplus/names/shader_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/shader_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_VERTEX_SHADER
	case GL_VERTEX_SHADER: return StrLit("VERTEX_SHADER");
#endif
#if defined GL_TESS_CONTROL_SHADER
	case GL_TESS_CONTROL_SHADER: return StrLit("TESS_CONTROL_SHADER");
#endif
#if defined GL_TESS_EVALUATION_SHADER
	case GL_TESS_EVALUATION_SHADER: return StrLit("TESS_EVALUATION_SHADER");
#endif
#if defined GL_GEOMETRY_SHADER
	case GL_GEOMETRY_SHADER: return StrLit("GEOMETRY_SHADER");
#endif
#if defined GL_FRAGMENT_SHADER
	case GL_FRAGMENT_SHADER: return StrLit("FRAGMENT_SHADER");
#endif
	default:;
}

