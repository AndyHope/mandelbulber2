/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Box Tiling 4d
 */

#include "all_fractal_definitions.h"

cFractalTransfStep::cFractalTransfStep() : cAbstractFractal()
{
	nameInComboBox = "T>Step";
	internalName = "transf_step";
	internalID = fractal::transfStep;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfStep::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 zc = (z);
	CVector4 colVec = CVector4(0.0, 0.0, 0.0, 0.0);
	zc *= fractal->transformCommon.scale3D111;

	double Step =  zc.y - 2.0 * floor(zc.y / 2.0);

	if (Step > 1.0)
	{
		zc.x += fractal->transformCommon.offset05;
		colVec.x += 1.0;
	}
	else colVec.y += 1.0;

	Step = zc.x - 2.0 * floor(zc.x / 2.0);

	if (Step > 1.0) colVec.z += 1.0;

	if (fractal->transformCommon.functionEnabledAxFalse)
	{
		zc.x = zc.x - floor(zc.x);
		zc.y = zc.y - floor(zc.y);
	}

	if (fractal->transformCommon.functionEnabledAy)
	{
		CVector4 boxSize = fractal->transformCommon.offset111;
		zc = fabs(zc) - boxSize;
		zc.x = max(zc.x, 0.0);
		zc.y = max(zc.y, 0.0);
		zc.z = max(zc.z, 0.0);
		double zcd;
		if (!fractal->transformCommon.functionEnabledAzFalse) zcd = zc.Length();
		else zcd = max(max(zc.x, zc.y), zc.z);
		zcd -= fractal->transformCommon.offset0;

		aux.dist = min(aux.dist, zcd / (aux.DE + 1.0f));
	}


	if (fractal->analyticDE.enabled)
	{
		if (!fractal->analyticDE.enabledFalse)
			aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		else
		{
			aux.DE = aux.DE * z.Length() * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		}
	}
	if (!fractal->transformCommon.functionEnabledAwFalse) z = zc;

	// aux.color
	if (fractal->foldColor.auxColorEnabled)
	{
		aux.color += fractal->foldColor.difs0000.x * colVec.x;
		aux.color += fractal->foldColor.difs0000.y * colVec.y;
		aux.color += fractal->foldColor.difs0000.z * colVec.z;
	}
}
