/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Mandelbox fractal known as AmazingBox or ABox, invented by Tom Lowe in 2010
 * @reference
 * http://www.fractalforums.com/ifs-iterated-function-systems/amazing-fractal/msg12467/#msg12467
 * This formula contains aux.color

 * This file has been autogenerated by tools/populateUiInformation.php
 * from the file "fractal_mandelbox_fast.cpp" in the folder formula/definition
 * D O    N O T    E D I T    T H I S    F I L E !
 */

REAL4 MandelboxFastIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	REAL4 ones = (REAL4){1.0f, 1.0f, 1.0f, 1.0f};
	z = fabs(z + ones) - fabs(z - ones) - z;

	REAL r2 = dot(z, z);

	if (r2 < fractal->mandelbox.mR2)
	{
		z *= fractal->mandelbox.mboxFactor1;
		aux->DE *= fractal->mandelbox.mboxFactor1;
	}
	else if (r2 < fractal->mandelbox.fR2)
	{
		REAL tglad_factor2 = fractal->mandelbox.fR2 / r2;
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
	}

	if (fractal->mandelbox.mainRotationEnabled) z = Matrix33MulFloat4(fractal->mandelbox.mainRot, z);

	z = z * fractal->mandelbox.scale;
	aux->DE = aux->DE * fabs(fractal->mandelbox.scale) + 1.0f;
	return z;
}