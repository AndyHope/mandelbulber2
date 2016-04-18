/*
 * material.cpp
 *
 *  Created on: 19 mar 2016
 *      Author: krzysztof
 */

#include "material.h"

cMaterial::cMaterial()
{
  // TODO Auto-generated constructor stub
  id = -1;
  shading = 0.0;
  specular = 0.0;
  specularWidth = 0.0;
  reflectance = 0.0;
  luminosity = 0.0;
  coloring_speed = 0.0;
  paletteOffset = 0.0;
  fresnelReflectance = 0.0;
  transparencyIndexOfRefraction = 0.0;
  transparencyOfInterior = 0.0;
  transparencyOfSurface = 0.0;
  useColorsFromPalette = false;
  useColorTexture = false;
  useDiffusionTexture = false;
  useLuminosityTexture = false;
  useBumpmapTexture = false;
  textureMappingType = mappingPlanar;
  colorTextureIntensity = 0.0;
  diffussionTextureIntensity = 0.0;
  luminosityTextureIntensity = 0.0;
  bumpmapTextureHeight = 0.0;
}

cMaterial::cMaterial(int _id, const cParameterContainer &materialParam, bool quiet)
{
  setParameters(_id, materialParam, quiet);
}

cMaterial::~cMaterial()
{
  // TODO Auto-generated destructor stub
}

//this static list will be use to optimize usage of material parameters
QStringList cMaterial::paramsList = {
    "shading",
    "specular",
    "specular_width",
    "reflectance",
    "luminosity",
    "bump_map_intensity",
    "transparency_of_surface",
    "transparency_of_interior",
    "transparency_index_of_refraction",
    "surface_color",
    "transparency_interior_color",
    "luminosity_color",
    "fresnel_reflectance",
    "texture_center",
    "texture_rotation",
    "texture_scale",
    "coloring_random_seed",
    "coloring_saturation",
    "coloring_speed",
    "coloring_palette_size",
    "coloring_palette_offset",
    "texture_mapping_type",
    "use_colors_from_palette",
    "file_color_texture",
    "file_diffusion_texture",
    "file_luminosity_texture",
    "file_bumpmap_texture",
    "surface_color_palette",
		"use_color_texture",
		"use_diffusion_texture",
		"use_luminosity_texture",
		"use_bumpmap_texture",
		"color_texture_intensity",
		"luminosity_texture_intensity",
		"diffusion_texture_intensity",
		"bumpmap_texture_height"
};

void cMaterial::setParameters(int _id, const cParameterContainer &materialParam, bool quiet = false)
{
  id = _id;
  shading = materialParam.Get<double>(Name("shading", id));
  specular = materialParam.Get<double>(Name("specular", id));
  specularWidth = materialParam.Get<double>(Name("specular_width", id));
  reflectance = materialParam.Get<double>(Name("reflectance", id));
  luminosity = materialParam.Get<double>(Name("luminosity", id)); //TODO lightness intensity
  transparencyIndexOfRefraction = materialParam.Get<double>(Name("transparency_index_of_refraction", id));
  transparencyOfInterior = materialParam.Get<double>(Name("transparency_of_interior", id));
  transparencyOfSurface = materialParam.Get<double>(Name("transparency_of_surface", id));
  paletteOffset = materialParam.Get<double>(Name("coloring_palette_offset", id));
  coloring_speed = materialParam.Get<double>(Name("coloring_speed", id));

  color = materialParam.Get<sRGB>(Name("surface_color", id));
  luminosityColor = materialParam.Get<sRGB>(Name("luminosity_color", id)); //TODO use of lightness color value
  transparencyInteriorColor = materialParam.Get<sRGB>(Name("transparency_interior_color", id));

  palette = materialParam.Get<cColorPalette>(Name("surface_color_palette", id));

  textureCenter = materialParam.Get<CVector3>(Name("texture_center", id));
  textureRotation = materialParam.Get<CVector3>(Name("texture_rotation", id));
  textureScale = materialParam.Get<CVector3>(Name("texture_scale", id));

  textureMappingType = (enumTextureMapping)materialParam.Get<int>(Name("texture_mapping_type", id));

  fresnelReflectance = materialParam.Get<bool>(Name("fresnel_reflectance", id));
  useColorsFromPalette = materialParam.Get<bool>(Name("use_colors_from_palette", id));

  useColorTexture = materialParam.Get<bool>(Name("use_color_texture", id));
  useDiffusionTexture = materialParam.Get<bool>(Name("use_diffusion_texture", id));
  useLuminosityTexture = materialParam.Get<bool>(Name("use_luminosity_texture", id));
  useBumpmapTexture = materialParam.Get<bool>(Name("use_bumpmap_texture", id));

  colorTextureIntensity = materialParam.Get<double>(Name("color_texture_intensity", id));
  diffussionTextureIntensity = materialParam.Get<double>(Name("diffusion_texture_intensity", id));
  luminosityTextureIntensity = materialParam.Get<double>(Name("luminosity_texture_intensity", id));
  bumpmapTextureHeight = materialParam.Get<double>(Name("bumpmap_texture_height", id));

	fractalColoring.coloringAlgorithm =
			(sFractalColoring::enumFractalColoringAlgorithm) materialParam.Get<int>(Name(	"fractal_coloring_algorithm",																																									id));
  fractalColoring.sphereRadius = materialParam.Get<double>(Name("fractal_coloring_sphere_radius", id));
  fractalColoring.lineDirection = materialParam.Get<CVector3>(Name("fractal_coloring_line_direction", id));


  if (useColorTexture)
    colorTexture = cTexture(materialParam.Get<QString>(Name("file_color_texture", id)), quiet);

  if (useDiffusionTexture)
    diffusionTexture = cTexture(materialParam.Get<QString>(Name("file_diffusion_texture", id)), quiet);

  if (useLuminosityTexture)
    luminosityTexture = cTexture(materialParam.Get<QString>(Name("file_luminosity_texture", id)), quiet);

  if (useBumpmapTexture)
    bumpmapTexture = cTexture(materialParam.Get<QString>(Name("file_bumpmap_texture", id)), quiet);

  rotMatrix.SetRotation2(textureRotation);
}
