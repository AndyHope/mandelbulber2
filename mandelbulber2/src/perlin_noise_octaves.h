/*
 * perlin_noise_octaves.h
 *
 *  Created on: 30 lip 2020
 *      Author: krzysztof
 */

// Code based on https://github.com/Reputeless/PerlinNoise/blob/master/PerlinNoise.hpp
//----------------------------------------------------------------------------------------
//
//	siv::PerlinNoise
//	Perlin noise library for modern C++
//
//	Copyright (C) 2013-2020 Ryo Suzuki <reputeless@gmail.com>
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

#ifndef MANDELBULBER2_SRC_PERLIN_NOISE_OCTAVES_H_
#define MANDELBULBER2_SRC_PERLIN_NOISE_OCTAVES_H_

#include <cstdint>
#include <array>
#include <random>

class cPerlinNoiseOctaves
{
public:
	cPerlinNoiseOctaves();
	~cPerlinNoiseOctaves() = default;

private:
	std::uint8_t p[512];

public:
	explicit cPerlinNoiseOctaves(std::uint32_t seed = std::default_random_engine::default_seed);

	static constexpr double Fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }

	static constexpr double Lerp(double t, double a, double b) { return a + t * (b - a); }

	static constexpr double Grad(std::uint8_t hash, double x, double y, double z)
	{
		const std::uint8_t h = hash & 15;
		const double u = h < 8 ? x : y;
		const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	static constexpr double Weight(std::int32_t octaves)
	{
		double amp = 1;
		double value = 0;

		for (std::int32_t i = 0; i < octaves; ++i)
		{
			value += amp;
			amp /= 2;
		}

		return value;
	}

	void reseed(std::uint32_t seed);

	///////////////////////////////////////
	//
	//	Noise [-1, 1]
	//

	double noise1D(double x) const;
	double noise2D(double x, double y) const;
	double noise3D(double x, double y, double z) const;

	///////////////////////////////////////
	//
	//	Noise [0, 1]
	//

	double noise1D_0_1(double x) const;
	double noise2D_0_1(double x, double y) const;
	double noise3D_0_1(double x, double y, double z) const;

	///////////////////////////////////////
	//
	//	Accumulated octave noise
	//	* Return value can be outside the range [-1, 1]
	//

	double accumulatedOctaveNoise1D(double x, std::int32_t octaves) const;
	double accumulatedOctaveNoise2D(double x, double y, std::int32_t octaves) const;
	double accumulatedOctaveNoise3D(double x, double y, double z, std::int32_t octaves) const;

	///////////////////////////////////////
	//
	//	Normalized octave noise [-1, 1]
	//

	double normalizedOctaveNoise1D(double x, std::int32_t octaves) const;
	double normalizedOctaveNoise2D(double x, double y, std::int32_t octaves) const;
	double normalizedOctaveNoise3D(double x, double y, double z, std::int32_t octaves) const;

	///////////////////////////////////////
	//
	//	Accumulated octave noise clamped within the range [0, 1]
	//

	double accumulatedOctaveNoise1D_0_1(double x, std::int32_t octaves) const;
	double accumulatedOctaveNoise2D_0_1(double x, double y, std::int32_t octaves) const;
	double accumulatedOctaveNoise3D_0_1(double x, double y, double z, std::int32_t octaves) const;

	///////////////////////////////////////
	//
	//	Normalized octave noise [0, 1]
	//

	double normalizedOctaveNoise1D_0_1(double x, std::int32_t octaves) const;
	double normalizedOctaveNoise2D_0_1(double x, double y, std::int32_t octaves) const;
	double normalizedOctaveNoise3D_0_1(double x, double y, double z, std::int32_t octaves) const;

	///////////////////////////////////////
	//
	//	Serialization
	//

	void serialize(std::array<std::uint8_t, 256> &s) const;
	void deserialize(const std::array<std::uint8_t, 256> &s);
};

#endif /* MANDELBULBER2_SRC_PERLIN_NOISE_OCTAVES_H_ */