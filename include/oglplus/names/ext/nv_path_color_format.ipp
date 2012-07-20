/*
 *  .file oglplus/names/ext/nv_path_color_format.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_color_format.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_LUMINANCE
	case GL_LUMINANCE: return StrLit("LUMINANCE");
#endif
#if defined GL_ALPHA
	case GL_ALPHA: return StrLit("ALPHA");
#endif
#if defined GL_INTENSITY
	case GL_INTENSITY: return StrLit("INTENSITY");
#endif
#if defined GL_LUMINANCE_ALPHA
	case GL_LUMINANCE_ALPHA: return StrLit("LUMINANCE_ALPHA");
#endif
#if defined GL_RGB
	case GL_RGB: return StrLit("RGB");
#endif
#if defined GL_RGBA
	case GL_RGBA: return StrLit("RGBA");
#endif
	default:;
}
