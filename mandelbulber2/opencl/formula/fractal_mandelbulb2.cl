/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.
 * Copyright (C) 2017 Mandelbulber Team   _>]|=||i=i<,
 *                                        \><||i|=>>%)
 * This file is part of Mandelbulber.     )<=i=]=|=i<>
 * The project is licensed under GPLv3,   -<>>=|><|||`
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Fractal formula created by Buddhi
 */

/* ### This file has been autogenerated. Remove this line, to prevent override. ### */

kernel void Mandelbulb2Iteration(global float3 *z, global sExtendedAux *aux)
{
	aux->r_dz = aux->r_dz * 2.0f * aux->r;

	float temp, tempR;
	tempR = native_sqrt(mad(z->x, z->x, z->y * z->y)); //+ 1e-061f
	z *= native_recip(tempR);
	temp = mad(z->x, z->x, -z->y * z->y);
	z->y = 2.0f * z->x * z->y;
	z->x = temp;
	z *= tempR;

	tempR = native_sqrt(mad(z->y, z->y, z->z * z->z)); //+ 1e-061f
	z *= native_recip(tempR);
	temp = mad(z->y, z->y, -z->z * z->z);
	z->z = 2.0f * z->y * z->z;
	z->y = temp;
	z *= tempR;

	tempR = native_sqrt(mad(z->x, z->x, z->z * z->z)); //+ 1e-061f
	z *= native_recip(tempR);
	temp = mad(z->x, z->x, -z->z * z->z);
	z->z = 2.0f * z->x * z->z;
	z->x = temp;
	z *= tempR;

	z = z * aux->r;
}