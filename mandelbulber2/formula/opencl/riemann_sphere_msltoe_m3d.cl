/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Generalized by darkbeam from a msltoe formula;
 * http://www.fractalforums.com/3d-fractal-generation/riemann-fractals/msg33500/#msg33500

 * This file has been autogenerated by tools/populateUiInformation.php
 * from the file "fractal_riemann_sphere_msltoe_m3d.cpp" in the folder formula/definition
 * D O    N O T    E D I T    T H I S    F I L E !
 */

REAL4 RiemannSphereMsltoeM3dIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	if (z.z > fractal->transformCommon.offsetA1) z * 1000.0; // fail bailout check
	else
	{
		z = Matrix33MulFloat4(fractal->transformCommon.rotationMatrix, z);
		REAL r = aux->r;
		REAL s, t;
		// if (r < 1e-21f) r = 1e-21f;
		z *= fractal->transformCommon.scale / r;
		REAL q = 1.0f / (1.0f - z.z);
		s = z.x * q;
		t = z.y * q;
		REAL w = 1.0f + s * s + t * t;
		REAL limit = fractal->transformCommon.scale8 * 8000.0f; // fudge
		if (w > limit) w = limit;

		s = fabs(native_sin(M_PI_F * s + fractal->transformCommon.offsetA0));
		t = fabs(native_sin(M_PI_F * t + fractal->transformCommon.offsetB0));
		s = fabs(s - fractal->transformCommon.offsetC0);
		t = fabs(t - fractal->transformCommon.offsetD0);

		r = -0.25f + fractal->transformCommon.offsetE0
				+ native_powr(r, (fractal->transformCommon.scale2 * w));
		w = 2.0f / (1.0f + s * s + t * t);
		z.x = r * s * w;
		z.y = r * t * w;
		z.z = r * (1.0f - w);
		z += fractal->transformCommon.offset001;
	}
	return z;
}