/*
 *  .file oglplus/names/tess_gen_primitive_spacing.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/tess_gen_primitive_spacing.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_FRACTIONAL_EVEN
	case GL_FRACTIONAL_EVEN: return StrLit("FRACTIONAL_EVEN");
#endif
#if defined GL_FRACTIONAL_ODD
	case GL_FRACTIONAL_ODD: return StrLit("FRACTIONAL_ODD");
#endif
#if defined GL_EQUAL
	case GL_EQUAL: return StrLit("EQUAL");
#endif
	default:;
}

