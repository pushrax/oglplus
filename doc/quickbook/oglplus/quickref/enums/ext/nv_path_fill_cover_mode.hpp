//  File doc/quickbook/oglplus/quickref/enums/ext/nv_path_fill_cover_mode.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/nv_path_fill_cover_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_ext_nv_path_fill_cover_mode

enum class PathNVFillCoverMode : GLenum
{
	ConvexHull                 = GL_CONVEX_HULL_NV,
	BoundingBox                = GL_BOUNDING_BOX_NV,
	BoundingBoxOfBoundingBoxes = GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV,
	FillCover                  = GL_PATH_FILL_COVER_MODE_NV
};

template <>
__Range<PathNVFillCoverMode> __EnumValueRange<PathNVFillCoverMode>(void);

__StrCRef __EnumValueName(PathNVFillCoverMode);

//]
