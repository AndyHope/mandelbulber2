/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Based on a DarkBeam fold formula adapted by Knighty
 * http://www.fractalforums.com/amazing-box-amazing-surf-and-variations/'new'-fractal-type-mandalay/msg81348/#msg81348

 * This file has been autogenerated by tools/populateUiInformation.php
 * from the file "fractal_mandalay_box_v2.cpp" in the folder formula/definition
 * D O    N O T    E D I T    T H I S    F I L E !
 */

REAL4 MandalayBoxV2Iteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	REAL colorAdd = 0.0f;
	REAL rrCol = 0.0f;

	// tglad fold
	if (fractal->transformCommon.functionEnabledAFalse
			&& aux->i >= fractal->transformCommon.startIterationsA
			&& aux->i < fractal->transformCommon.stopIterationsA)
	{
		z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x)
					- fabs(z.x - fractal->transformCommon.additionConstant111.x) - z.x;
		z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y)
					- fabs(z.y - fractal->transformCommon.additionConstant111.y) - z.y;
		if (fractal->transformCommon.functionEnabled)
		{
			z.z = fabs(z.z + fractal->transformCommon.additionConstant111.z)
						- fabs(z.z - fractal->transformCommon.additionConstant111.z) - z.z;
		}
	}

	REAL signX = sign(z.x);
	REAL signY = sign(z.y);
	REAL signZ = sign(z.z);

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux->i >= fractal->transformCommon.startIterationsP
			&& aux->i < fractal->transformCommon.stopIterationsP)
	{
		if (fractal->transformCommon.functionEnabledAx) z.x = fabs(z.x);
		if (fractal->transformCommon.functionEnabledAy) z.y = fabs(z.y);
		if (fractal->transformCommon.functionEnabledAz) z.z = fabs(z.z);
	}
	else
	{
		z = fabs(z);
	}

	REAL4 fo = fractal->transformCommon.additionConstant0555;
	REAL4 g = fractal->transformCommon.offsetA000;
	REAL4 p = z;
	REAL4 q = z;

	REAL t1, t2, v, v1;

	if (p.z > p.y)
	{
		REAL temp = p.y;
		p.y = p.z;
		p.z = temp;
	}
	t1 = p.x - 2.0f * fo.x;
	t2 = p.y - 4.0f * fo.x;
	v = max(fabs(t1 + fo.x) - fo.x, t2);
	v1 = max(t1 - g.x, p.y);
	v = min(v, v1);
	q.x = min(v, p.x);

	if (!fractal->transformCommon.functionEnabledSwFalse)
		p = z;
	else
		p = q;

	if (p.x > p.z)
	{
		REAL temp = p.z;
		p.z = p.x;
		p.x = temp;
	}
	t1 = p.y - 2.0f * fo.y;
	t2 = p.z - 4.0f * fo.y;
	v = max(fabs(t1 + fo.y) - fo.y, t2);
	v1 = max(t1 - g.y, p.z);
	v = min(v, v1);
	q.y = min(v, p.y);

	if (!fractal->transformCommon.functionEnabledSwFalse)
		p = z;
	else
		p = q;

	if (p.y > p.x)
	{
		REAL temp = p.x;
		p.x = p.y;
		p.y = temp;
	}
	t1 = p.z - 2.0f * fo.z;
	t2 = p.x - 4.0f * fo.z;
	v = max(fabs(t1 + fo.z) - fo.z, t2);
	v1 = max(t1 - g.z, p.x);
	v = min(v, v1);
	q.z = min(v, p.z);

	z = q;

	z.x *= signX;
	z.y *= signY;
	z.z *= signZ;

	// spherical fold
	REAL useScale = 1.0f;
	if (aux->i >= fractal->transformCommon.startIterationsS
			&& aux->i < fractal->transformCommon.stopIterationsS)
	{

		REAL rr = dot(z, z);
		rrCol = rr;
		if (rr < fractal->transformCommon.minR2p25)
		{
			REAL tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
			z *= tglad_factor1;
			aux->DE *= tglad_factor1;
		}
		else if (rr < fractal->transformCommon.maxR2d1)
		{
			REAL tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
			z *= tglad_factor2;
			aux->DE *= tglad_factor2;
		}
	}

	// scale
	useScale = aux->actualScaleA + fractal->transformCommon.scale2;
	z *= useScale;
	aux->DE = aux->DE * fabs(useScale) + 1.0f;

	if (fractal->transformCommon.functionEnabledKFalse
			&& aux->i >= fractal->transformCommon.startIterationsK
			&& aux->i < fractal->transformCommon.stopIterationsK)
	{
		// update actualScaleA for next iteration
		REAL vary = fractal->transformCommon.scaleVary0
								* (fabs(aux->actualScaleA) - fractal->transformCommon.scaleC1);
		aux->actualScaleA -= vary;
	}

	// rotation
	if (fractal->transformCommon.rotationEnabled
			&& aux->i >= fractal->transformCommon.startIterationsR
			&& aux->i < fractal->transformCommon.stopIterationsR)
	{
		z = Matrix33MulFloat4(fractal->transformCommon.rotationMatrix, z);
	}

	if (fractal->analyticDE.enabledFalse)
		aux->DE = aux->DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

	if (fractal->foldColor.auxColorEnabledFalse)
	{
		if (rrCol < fractal->transformCommon.maxR2d1)
		{
			colorAdd += fractal->mandelbox.color.factorSp2 * (fractal->transformCommon.maxR2d1 - rrCol);
			if (rrCol < fractal->transformCommon.minR2p25)
				colorAdd += fractal->mandelbox.color.factorSp1 * (fractal->transformCommon.minR2p25 - rrCol)
										+ fractal->mandelbox.color.factorSp2
												* (fractal->transformCommon.maxR2d1 - fractal->transformCommon.minR2p25);
		}
		aux->color += colorAdd;
	}

	// temp code
	p = fabs(z);
	aux->dist = max(p.x, max(p.y, p.z));
	aux->dist = aux->dist / aux->DE;

	return z;
}