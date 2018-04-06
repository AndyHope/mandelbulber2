/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-18 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * data structures for primitive objects for OpenCL kernels
 */

#ifndef MANDELBULBER2_OPENCL_PRIMITIVES_CL_H_
#define MANDELBULBER2_OPENCL_PRIMITIVES_CL_H_

#ifndef OPENCL_KERNEL_CODE
#include "object_type_cl.h"
#include "cl_kernel_include_headers.h"
#endif

// object data
typedef struct
{
	cl_int enable;
	cl_int objectId;
	cl_float3 position;
	cl_float3 size;
	cl_int materialId;
	enumObjectTypeCl objectType;
	matrix33 rotationMatrix;
} objectDataCl;

// primitive specified parameters
typedef struct
{
	cl_int empty;
} sPrimitivePlaneCl;

typedef struct
{
	cl_int empty;
	cl_float rounding;
	cl_float3 repeat;
} sPrimitiveBoxCl;

typedef struct
{
	cl_int empty;
	cl_float radius;
	cl_float3 repeat;
} sPrimitiveSphereCl;

typedef struct
{
	cl_int empty;
	cl_int waveFromObjectsEnable;
	cl_float relativeAmplitude;
	cl_float animSpeed;
	cl_float length;
	cl_float waveFromObjectsRelativeAmplitude;
	cl_int iterations;
	cl_int animFrame;
} sPrimitiveWaterCl;

typedef struct
{
	cl_int empty;
	cl_float radius;
	cl_float radius_lpow;
	cl_float tube_radius;
	cl_float tube_radius_lpow;
	cl_float3 repeat;
} sPrimitiveConeCl;

typedef struct
{
	cl_int empty;
	cl_float radius;
	cl_float3 repeat;
} sPrimitiveTorusCl;

typedef struct
{
	cl_float radius;
} sPrimitiveCircleCl;

typedef struct
{
	cl_float height;
	cl_float width;
} sPrimitiveRectangleCl;

// union - variable container for primitive data
typedef union {
	sPrimitivePlaneCl plane;
	sPrimitiveBoxCl box;
	sPrimitiveWaterCl water;
	sPrimitiveConeCl cone;
	sPrimitiveTorusCl torus;
	sPrimitiveCircleCl circle;
	sPrimitiveRectangleCl rectangle;
} uPrimitiveCl;

// full definition of primitive
typedef struct
{
	objectDataCl object; // structure
	uPrimitiveCl data;	 // union !!!
} sPrimitiveCl;

#endif /* MANDELBULBER2_OPENCL_PRIMITIVES_CL_H_ */