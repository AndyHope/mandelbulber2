/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Testing transform2
 *

 * This file has been autogenerated by tools/populateUiInformation.php
 * from the file "fractal_testing_transform2.cpp" in the folder formula/definition
 * D O    N O T    E D I T    T H I S    F I L E !
 */

REAL4 TestingTransform2Iteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	REAL4 p = z;
	REAL dd = aux->DE;
	REAL m = 0.0;
	REAL tp = 1.0;
	REAL4 signs = z;
	signs.x = sign(z.x);
	signs.y = sign(z.y);
	signs.z = sign(z.z);
	z = fabs(z);
	z -= fractal->transformCommon.offset000;
	REAL trr = dot(z, z);
	if (!fractal->transformCommon.functionEnabledAFalse)
	{
		tp = min(max(native_recip(trr), fractal->transformCommon.scale1), fractal->transformCommon.scale4);
	}
	else
	{
		tp = trr + sin(trr * M_PI * fractal->transformCommon.scale2) * fractal->transformCommon.scaleC1 + fractal->transformCommon.scaleC1;
		tp = min(max(1.0 / tp, fractal->transformCommon.scale1), fractal->transformCommon.scale4);

	}

	/*else
	{
		if (trr < fractal->transformCommon.scale4)
		{
			tp = native_divide(fractal->transformCommon.scale4, fractal->transformCommon.scale1);
		}
		else if (trr < fractal->transformCommon.scale1)
		{
			tp = native_divide(fractal->transformCommon.scale1, trr);
			tp = native_recip(tp);
		}
	}*/

	if (fractal->transformCommon.functionEnabledJFalse)
	{
		if (trr < fractal->transformCommon.scale1)
		{

			tp = native_recip(trr);
			tp = min(tp, fractal->transformCommon.scale4);
		}
		else
		{
			tp = fractal->transformCommon.scale1;
		}

	}



	z += fractal->transformCommon.offset000;
	z *= tp;
	aux->DE *= tp;
	z *= signs;

	if (fractal->transformCommon.functionEnabledBFalse
			&& aux->i >= fractal->transformCommon.startIterationsB
			&& aux->i < fractal->transformCommon.stopIterationsB)
	{
		REAL rr = dot(p, p);
		if (rr < 1.0)
		{
			p += fractal->mandelbox.offset;
			if (rr < fractal->transformCommon.scale025)
				m = fractal->transformCommon.scale025;
			else m = rr;
			m = native_recip(m);
			p *= m;
			dd *= m;
			p -= fractal->mandelbox.offset;
		}




		/*p += fractal->mandelbox.offset;
		m = min(max(native_recip(rr), 1.0f), native_recip(fractal->transformCommon.scale025));
		p *= m;
		dd *= m;
		p -= fractal->mandelbox.offset;*/

		z = p + (z - p) * fractal->transformCommon.scale1;
		aux->DE = dd + (aux->DE - dd) * fractal->transformCommon.scale1;
	}

	if (fractal->foldColor.auxColorEnabledFalse)
	{
		aux->color += tp * fractal->mandelbox.color.factorSp1;
		aux->color += m * fractal->mandelbox.color.factorSp2;
	}

	// DE tweak
	if (fractal->analyticDE.enabledFalse)
		aux->DE = mad(aux->DE, fractal->analyticDE.scale1, fractal->analyticDE.offset0);
	return z;
}
