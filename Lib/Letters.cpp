// Letters.cpp - display non-negative alphabet characters as grayscale text
// Copyright (c) 2024 Jules Bloomenthal, all rights reserved. Commercial use requires license.

#include <glad.h>
#include "Draw.h"
#include "GLXtras.h"
#include "IO.h"
#include "Letters.h"
#include <stdio.h>

namespace {

// images are 13 lines, each with 284 grayscale values; a value is represented as two hexadecimal characters
const char *lowerCaseImage = "\
FFFFFFFFFFFFFFFFFFD8000000D8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3B00007AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB90000000000FFFFFFFFFFFFFFFFFFFFFFFF3B00005CFFFFFFFFFFFFFFFFFFFFFF0000D8FFFFFFFFFFFFFFFFD80000D8FFFFFF9B000000FFFFFFFFFFFFFFFFD8000000009BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5C1DFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\
FFFFFFFFFFFFFFFFFFD8000000D8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3B00007AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD8000000000000B9FFFFFFFFFFFFFFFFFFFFFF3B00005CFFFFFFFFFFFFFFFFFFFFFF0000D8FFFFFFFFFFFFFFFFD80000D8FFFFFF9B000000FFFFFFFFFFFFFFFFD8000000009BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\
FFFFFFFFFFFFFFFFFFFFFF3B00D8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9B007AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9B007AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB9005CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D00FFFFFFFFFFFFFFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\
FF5C000000005CFFFFFFFF3B00B900000000FFFFFFFFFFFF5C0000005C7A3BFFFFFFD8000000009B007AFFFFFFD8000000009BFFFFFFFF9B000000000000009BFFFFFFB90000003B5C00005CFFB9005C3B00001DFFFFFFFFD8000000009BFFFFFFFFFF9B0000000000009BFFFFFFFF1D00FF000000009BFFFFFFFFFF7A009BFFFFFFD800001D00005C1D0000B9FFD800001D5C000000FFFFFFFFFFFF3B0000005CFFFFD8000000B900000000FFFFFFFFFFD8000000009B000000FF5C000000D85C00003BFFFFFFFF000000000000FFFFFF5C00000000000000D8FF7A00001DFFFF9B0000B9FF3B0000003BFF1D0000003B3B000000FFFFB90000005CD80000003BFF1D000000FF7A0000007AFF00000000D8FFB900000000000000B9\
D80000000000005CFFFFFF3B00000000000000B9FFFFFF0000000000000000FFFF9B000000000000007AFFFF7A0000000000003BFFFFFF9B000000000000009BFFFF7A00000000000000005CFFB90000000000001DFFFFFFD8000000009BFFFFFFFFFF9B0000000000009BFFFFFFFF1D00FF3B0000009BFFFFFFFFFF7A009BFFFFFFD800000000000000000000FFD80000000000000000FFFFFFD800000000000000FFD8000000000000000000B9FFFF9B000000000000000000FF5C0000000000000000B9FFD800000000000000D8FFFF5C00000000000000D8FF7A00001DFFFF9B0000B9FF3B0000003BFF1D0000003B3B000000FFFFB90000005CD80000003BFF1D000000FF7A0000007AFF00000000D8FFB900000000000000D8\
FFFFFFFFFFD8003BFFFFFF3B0000D8FFFF7A0000FFFF5C003BFFFFFFD80000FFD800009BFFFFB900007AFFD80000FFFFFFFF5C009BFFFFFFFF9B007AFFFFFFFFFFD80000B9FFFF7A0000B9FFFFB90000B9FFFF3B00D8FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFF7A009BFFFFFFFF1D001D0000FFFFFFFFFFFFFFFF7A009BFFFFFFFFFF0000D89B003BFF3B00D8FFFF00009BFFFF3B00B9FFFF1D005CFFFFFF3B005CFFFF3B0000D8FFFF7A0000FFD800009BFFFFB900007AFFFFFFFF3B00001DFFFFFFFFFFB9007AFFFFFF5C00FFFFFFFFFF1D00FFFFFFFFFFFFFFFF001DFFFFFF5C00B9FFFFD8001DFFFFFF0000FFFFFF1D00FF5C009BD8003BFFFFFF1D0000D800005CFFFFFF9B005CFFFFD8001DFFFFFFB9007AFF7A0000D8FF\
FFB900000000001DFFFFFF3B00B9FFFFFFFF5C00B9FF001DFFFFFFFFFF3B3BFF9B007AFFFFFFFF9B007AFF9B00000000000000003BFFFFFFFF9B007AFFFFFFFFFF9B007AFFFFFFFF3B00B9FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFF7A009BFFFFFFFF1D00003BFFFFFFFFFFFFFFFFFF7A009BFFFFFFFFFF005CFF9B00B9FF3B00D8FFFF001DFFFFFF5C00B9FFD8003BFFFFFFFFFF1D00FFFF3B00B9FFFFFFFF5C00B99B007AFFFFFFFF7A007AFFFFFFFF3B009BFFFFFFFFFFFFFF1D000000007AFFFFFFFFFFFF1D00FFFFFFFFFFFFFFFF001DFFFFFF5C00B9FFFFFF3B00B9FF7A007AFFFFFF5C00B900003B9B007AFFFFFFFF7A0000009BFFFFFFFFFF1D00D8FF5C009BFFFFFFFFFFFF7A0000D8FFFF\
7A0000000000001DFFFFFF3B00D8FFFFFFFF7A00B9FF001DFFFFFFFFFFFFFFFF9B009BFFFFFFFF9B007AFF9B00000000000000003BFFFFFFFF9B007AFFFFFFFFFF9B007AFFFFFFFF3B00B9FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFF7A009BFFFFFFFF1D0000003BFFFFFFFFFFFFFFFF7A009BFFFFFFFFFF00B9FF9B1DFFFF3B00D8FFFF001DFFFFFF5C00B9FFD8003BFFFFFFFFFF1D00FFFF3B00B9FFFFFFFF5C00B99B007AFFFFFFFF9B007AFFFFFFFF3B00D8FFFFFFFFFFFFFFFFFFB900000000D8FFFFFFFF1D00FFFFFFFFFFFFFFFF001DFFFFFF5C00B9FFFFFFB9003BFF1D00FFFFFFFF9B003B0000003B00B9FFFFFFFF3B0000003BFFFFFFFFFF9B005CB9001DFFFFFFFFFFFF7A0000D8FFFFFF\
001DFFFFFFFF001DFFFFFF3B001DFFFFFFB90000D8FF3B005CFFFFFFFF7A00B9B90000D8FFFFFF00007AFFD8001DFFFFFFFFFFFFFFFFFFFFFF9B007AFFFFFFFFFFD80000B9FFFF7A0000B9FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFF7A009BFFFFFFFF1D00FF1D001DFFFFFFFFFFFFFF7A009BFFFFFFFFFF00FFFF9B5CFFFF3B00D8FFFF001DFFFFFF5C00B9FFFF1D005CFFFFFF3B003BFFFF3B0000D8FFFF9B0000FFD80000B9FFFFB900007AFFFFFFFF3B00D8FFFFFFFFFFFF5C00D8FFFFFF9B007AFFFFFFFF1D00FFFFFF7A00B9FFFF001DFFFF9B0000B9FFFFFFFF3B005C005CFFFFFFFFD80000007A000000FFFFFFD800003BFF1D0000FFFFFFFFFF1D0000009BFFFFFFFFFF7A0000D8FF9B009B\
1D00000000000000009D0000000000000000007AFFFFD80000000000000000D8FF5C000000000000000000FF7A000000000000003BFFFF5C00000000000000D8FFFF7A00000000000000B9FF9B0000003BFF3B0000009BFF1D000000000000005CFFFFFFFFFFFFFF7A009BFFFF9B000000FFFF1D000000D8FF1D000000000000005CD8000000FF9B005CFF3B00009D00000000FF3B0000009BFFB900000000000000FFFFFF3B000000000000009BFFFF7A000000000000007AFFFF000000000000003BFFFFFF3B00000000000000B9FFFFFFFF5C000000000000B9FFFF1D000000000000009BFFFFFFB9000000D8FFFFFFFFFF1D003BFF1D003BFFFF7A0000003BFF1D0000009BFFFFFFB900003BFFFFFFFFFF7A000000000000009B\
FF1D000000B90000009D000000D800000000D8FFFFFFFFFF1D000000001DFFFFFFFF9B000000009B000000FFFFD8000000000000FFFFFF5C00000000000000D8FFFFFFB90000003B5C00B9FF9B0000003BFF3B0000009BFF1D000000000000005CFFFFFFFFFFFFFF7A009BFFFF9B000000FFB900000000D8FF1D000000000000005CD8000000FF9B005CFF3B00009D00000000FF3B0000009BFFFFFF1D0000005CFFFFFFFF3B00B900000000FFFFFFFFFFD8000000009B007AFFFF000000000000003BFFFFFF5C000000000000FFFFFFFFFFFFFF3B0000003BFFFFFFFFFF0000005C5C00009BFFFFFFFF1D005CFFFFFFFFFFFF3B009BFF7A007AFFFF7A0000003BFF1D0000009BFFFFFFFF1D00B9FFFFFFFFFF7A000000000000009B\
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D00D8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D00B9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3B00D8FFFFFFFFFFFFFFFFFFFFFFFFFFFF9B007AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9B003BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A00000000003BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9B00000000001DFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD800000000009BFFFFFFFFFFFFFFFFFFFF7A0000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5C00000000005CFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

const char *upperCaseImage = "\
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\
7A000000009BFFFFFFFF3B00000000000000FFFFFFFFFFFF5C0000009B5C1DFF1D000000000000B9FFFFFF3B00000000000000005CFFD80000000000000000009BFFFFFF5C0000009B5C3BFFB90000001DFF00000000B9FF7A00000000000000B9FFFFFFFF9B000000000000005C000000B9FF7A0000003B9B00000000001DFFFFFFD8000000D8FFFFFF9B0000000000009BFFD8000000005CFFFFFF5C0000007AFFFFFFFF1D0000000000005CFFFFFFFFFF5C0000007AFFFFFF3B0000000000001DFFFFFFFFFFFF3B000000B900B9FFB9000000000000000000D81D00003BFFFFFF0000000000000000B9FF9B00000000000000007AFF5C000000003B0000007AFF5C0000005C3B0000009BFF9B0000005CFF9B00000000000000B9\
7A000000001DFFFFFFFF3B0000000000000000D8FFFFFF0000000000000000FF1D000000000000007AFFFF3B00000000000000005CFFD80000000000000000009BFFFF1D00000000000000FFB90000001DFF00000000B9FF7A00000000000000B9FFFFFFFF9B000000000000005C000000B9FF7A0000003B9B00000000001DFFFFFFD80000005CFFFFFF3B00000000000000FFD8000000005CFFFF0000000000001DFFFFFF1D000000000000003BFFFFFF0000000000001DFFFF3B0000000000000000FFFFFFFF1D0000000000009BFFB9000000000000000000D81D00003BFFFFFF0000000000000000B9FF9B00000000000000007AFF5C000000003B0000007AFF5C0000005C3B0000007AFF9B0000005CFF9B00000000000000B9\
FFFF7A000000B9FFFFFFFFB9005CFFFFFF7A007AFFFF3B001DFFFFFF9B0000FFFF3B00D8FFFFB90000D8FFFFB9005CFFFFFFB9005CFFFFFF5C00B9FFFFFF7A009BFF5C001DFFFFFFB90000FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFFFF001DFFFFFFB9005CFFFF5C0000FFFFFFFFD8003BFFFFFFFFFFFFB9000000FFFFD8000000D8FF3B00005CFFFF9B007AFFFF1D003BFFFFFF00005CFFFFFF7A009BFFFFFF0000D8FF3B003BFFFFFF00005CFFFFB9005CFFFFFF3B007AFFFFB9001DFFFFFF1D009BFFB9005CFF7A009BFF3B00D8FF3B00D8FFFFFFB9005CFFD8001DFFFFFFFFFF0000FF9B007AFFFFFFFFFF5C00B9FFD80000B9FF9B0000FFFFFFB90000FFFFD80000D8FFFF9B007AFFFF7A001DFF\
FFFF1D00B9005CFFFFFFFFB9005CFFFFFF5C009BFFD8001DFFFFFFFFFF3B1DFFFF3B00D8FFFFFF9B005CFFFFB9005CFF1D1DB9007AFFFFFF5C00B97A00B97A00B9D80000FFFFFFFFFF3B3BFFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFFFF001DFFFFFFB9005CFF3B001DFFFFFFFFFFD8003BFFFFFFFFFFFFB90000009BFF7A000000D8FF3B000000B9FF9B007AFFB9003BFFFFFFFFFF0000D8FFFF7A009BFFFFFF7A00B9B9003BFFFFFFFFFF0000D8FFB9005CFFFFFFB9007AFFFF9B007AFFFFFFB900B9FFB9005CFF7A009BFF3B00D8FF3B00D8FFFFFFB9005CFFFF3B00B9FFFFFF7A007AFFB9005CFF3B007AFF3B00D8FFFF9B00009B0000B9FFFFFFFF7A003BFF1D009BFFFFFFB9007AFFB90000FFFF\
FFB9005CFF3B00D8FFFFFFB90000000000001DFFFFB9007AFFFFFFFFFFFFFFFFFF3B00D8FFFFFFFF001DFFFFB90000000000FFFFFFFFFFFF5C000000009BFFFFFFB9007AFFFFFFFFFFFFFFFFFFB900000000000000B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFFFF001DFFFFFFB9005C1D001DFFFFFFFFFFFFD8003BFFFFFFFFFFFFB9003B001DFF1D003B00D8FF3B009B001DFF9B007AFF7A00B9FFFFFFFFFF7A009BFFFF7A009BFFFFD80000D87A00B9FFFFFFFFFF7A009BFFB9005CFFFFD800009BFFFFFF00001DFFFFFFFFFFFFB9007AFF7A009BFF3B00FFFF3B00D8FFFFFFB9005CFFFFB9003BFFFFFF1D00D8FFD8003BFF00001DFF1D1DFFFFFFFF7A0000009BFFFFFFFFFFFF1D0000005CFFFFFFFFFFFFFFFF0000B9FFFF\
FF5C00B9FF9B007AFFFFFFB9000000000000007AFF9B007AFFFFFFFFFFFFFFFFFF3B00D8FFFFFFFF001DFFFFB90000000000FFFFFFFFFFFF5C000000009BFFFFFF9B007AFFFF1D000000003BFFB900000000000000B9FFFFFFFFFF7A009BFFFFFFFFFFFFFFFFFFFFFF001DFFFFFFB9000000003BFFFFFFFFFFFFD8003BFFFFFFFFFFFFB9005C3B005C005C3B00D8FF3B00D85C007A9B007AFF5C00B9FFFFFFFFFF9B007AFFFF7A0000000000005CFF5C00B9FFFFFFFFFF9B009BFFB90000000000003BFFFFFFFFD800000000007AFFFFFFFFFFFF7A009BFFFFFFFFFF3B00D8FFFFFFB9005CFFFFFF1D00D8FF9B005CFFFFFF001D9B000000D8003BFFFFFFFFFF1D003BFFFFFFFFFFFFFFD8000000FFFFFFFFFFFFFFFF1D007AFFFFFF\
D80000000000001DFFFFFFB9005CFFFFFFB90000D8B9007AFFFFFFFFFFFFFFFFFF3B00D8FFFFFFFF001DFFFFB9005CFF1D1DFFFFFFFFFFFF5C00B97A00B9FFFFFFB9007AFFFF1D000000003BFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFF3B1DFFFFFFFF001DFFFFFFB900001D00003BFFFFFFFFFFD8003BFFFFFF7A00B9B9005C9B000000B93B00D8FF3B00D8FF00007A007AFF7A00B9FFFFFFFFFF7A009BFFFF7A0000000000B9FFFF5C00B9FFFFFFFFFF7A009BFFB900000000003BFFFFFFFFFFFFFFFFFF3B00009BFFFFFFFFFF7A009BFFFFFFFFFF3B00D8FFFFFFB9005CFFFFFF9B005CFF3B00B9FFFFFF1D005C005C003B005CFFFFFFFF5C0000007AFFFFFFFFFFFFFF7A009BFFFFFFFFFFFFFF5C005CFFFFFFFF\
7A00000000000000B9FFFFB9005CFFFFFFFF7A00B9D8001DFFFFFFFFFFFFFFFFFF3B00D8FFFFFFB9003BFFFFB9005CFFFFFFFF1D1DFFFFFF5C00B9FFFFFFFFFFFFD8003BFFFFFFFFFF1D00FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFF1D00FFFFFFFF003BFFFFFFB9005CFFFF1D007AFFFFFFFFD8003BFFFFFF7A009BB9005CFF1D001DFF3B00D8FF3B00D8FF9B0000007AFFB9003BFFFFFFFFFF0000D8FFFF7A009BFFFFFFFFFFFF9B003BFFFFFFFFFF0000D8FFB9005CFFFF1D003BFFFFFF5C00FFFFFFFFD8003BFFFFFFFFFF7A009BFFFFFFFFFF3B00D8FFFFFFB9007AFFFFFFFF1D00B9003BFFFFFFFF3B00001DD80000007AFFFFFF7A001DFF00009BFFFFFFFFFFFF7A009BFFFFFFFFFFFF7A001DFFFFD8005C\
1D00FFFFFFFFB9003BFFFFB9005CFFFFFFFF3B00B9FF3B001DFFFFFFFF3B00FFFF3B00D8FFFFFF00009BFFFFB9005CFFFFFFFF1D00FFFFFF5C00B9FFFFFFFFFFFFFF1D005CFFFFFFFF0000FFFFB9005CFFFFFF5C00B9FFFFFFFFFF7A009BFFFFFFFFFF1D00B9FFFF5C005CFFFFFFB9005CFFFFD80000FFFFFFFFD8003BFFFFFF7A009BB9005CFF7A007AFF3B00D8FF3B00D8FFFF3B00007AFFFF1D003BFFFFFF00005CFFFFFF7A009BFFFFFFFFFFFFFF00003BFFFFFF00005CFFFFB9005CFFFFFF1D009BFFFF3B005CFFFFFF5C003BFFFFFFFFFF7A009BFFFFFFFFFF7A001DFFFFFF0000B9FFFFFFFF7A0000009BFFFFFFFF5C00005CFF3B00009BFFFF9B0000D8FFB90000B9FFFFFFFFFF7A009BFFFFFFFFFFB90000FFFFFFB9005C\
0000009BFF5C000000001D00000000000000001DFFFFFF000000000000001DFF1D000000000000005CFFFF3B000000000000000000FFD8000000000000B9FFFFFFFFD80000000000000000FFB90000001DFF00000000B9FF7A00000000000000B9FFFF1D000000000000D8FFFF5C000000B9FFFF5C00001D9B0000000000000000005E000000009BFF7A000000000000000000FFB900007AFFFFFF0000000000001DFFFFFF1D00000000009BFFFFFFFF9B0000000000001DFFFF3B000000009BFFD800001DFF3B00000000000000B9FFFFFF1D00000000003BFFFFFFFF1D00000000005CFFFFFFFFFFFF00001DFFFFFFFFFF7A0000B9FF9B0000B9FF1D0000003BFF1D0000003BFFFF1D00000000003BFFFFFF3B000000000000005C\
0000009BFF5C000000001D000000000000001DFFFFFFFFFF5C000000007AFFFF1D0000000000009BFFFFFF3B000000000000000000FFD8000000000000B9FFFFFFFFFFFF3B000000007AFFFFB90000001DFF00000000B9FF7A00000000000000B9FFFFFFD80000001DFFFFFFFF5C000000B9FFFFD800001D9B0000000000000000005E000000009BFF7A000000000000000000FFFF5C007AFFFFFFFF5C0000007AFFFFFFFF1D00000000009BFFFFFFFFFFB9000000007AFFFFFF3B000000009BFFFF9B001DFF5C1DD800000000FFFFFFFFFF1D00000000003BFFFFFFFFFF5C0000007AFFFFFFFFFFFFFF5C007AFFFFFFFFFFB9001DFFFFD80000D8FF1D0000003BFF1D0000003BFFFF1D00000000003BFFFFFF3B000000000000005C\
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1D000000D8D800B9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

// next 10 lines each with 82 grayscale values, each value represented as two hexadecimal characters
const char *numberImage = "\
FFEC7A110034C3FFFFDD98340047FFFFFFFFA723002389FFFFFF000000117AFFFFFFFFFFC3000089FFFF890000000000FFFFFFFFA734000089FF89000000000000C3FFDD57000023A7FFFFEC69110034B5FF\
FF470000000011DDFF5700000047FFFFFF980000000000B5FFFF000000000098FFFFFFFF23000089FFFF890000000000FFFFFF690000000089FF89000000000000C3FF340000000000D0FF470000000000DD\
D00011DDFF690069FF987AB50047FFFFFFEC47DDFF89007AFFFFFFFFFF980047FFFFFF89007A0089FFFF8900C3FFFFFFFFFFC30023B5FFFFFFFFFFFFFFFFEC1123FFFF0034ECFFA700C3DD0023DDFF890089\
890098FFC3340034FFFFFFC30047FFFFFFFFFFFFFFB50089FFFFFFFFFF890089FFFFDD0057C30089FFFF8900C3FFFFFFFFFF7A00B5FFFFFFFFFFFFFFFFFF890089FFFF2311B5DD3411ECC30023ECFFA70047\
8900A74700000000FFFFFFC30047FFFFFFFFFFFFFF5700C3FFFFFF00000057ECFFFF4711DDC30089FFFF8900000034B5FFFF47007A230034D0FFFFFFFFEC1111ECFFFFD023000000D0FFFF11000000000047\
8900000023B50000FFFFFFC30047FFFFFFFFFFFF980069FFFFFFFF0000000069FFB50098FFC30089FFFF890000000000C3FF47000000000011FFFFFFFF890089FFFFFFB51123230034ECFFD03400237A0047\
89001189FFDD0047FFFFFFC30047FFFFFFFFFF980069FFFFFFFFFFFFFFC31100DD4700000000000000FFFFFFFFEC7A0089FF470069ECEC3400C3FFFFEC1111ECFFFFEC1123ECEC570098FFFFFFFFFFB5007A\
B50034DDEC57007AFFFFFFC30047FFFFFFFF690089FFFFFFFFFFFFFFFFDD2300DD4700000000000000FFFFFFFFEC690089FF8900A7FFDD2300D0FFFF890089FFFFFFC30034FFFFA70089FFFFFFFFB52300C3\
FF340000000011DDFF47000000000047FF98000000000000FFC3000000000047FFFFFFFFFFC30089FFFF470000000011DDFFDD000000000047FFFFEC1111ECFFFFFFEC110000000000C3FF470000000069FF\
FFEC69000057D0FFFF47000000000047FF89000000000000FFC30000003489ECFFFFFFFFFFC30089FFFF4700001169DDFFFFFFB534001169ECFFFF890089FFFFFFFFFFC334000034B5FFFF4700003498FFFF";

// transform 2D vertex by view, separate uv from vec4
const char *vertexShader = R"(
	#version 130
	in vec4 point;
	out vec2 vUv;
	uniform mat4 view;
	void main() {
		gl_Position = view*vec4(point.xy, 0, 1);
		vUv = point.zw;
	}
)";

// opacity depends on darkness of texture map
const char *pixelShader = R"(
	#version 130
	in vec2 vUv;
	out vec4 pColor;
	uniform sampler2D textureImage;
	uniform vec3 color;
	void main() {
		float a = texture(textureImage, vUv).r;
		pColor = vec4(color, 1-a);
	}
)";

GLuint shaderProgram = 0, vBufferId = 0;
GLuint textureNameLower = 0, textureNameUpper = 0, textureNameNumber = 0;
int textureUnitLower = 2, textureUnitUpper = 3, textureUnitNumber = 4; // this dies if GLUint?!

} // end namespace

int MakeLetterTexture(unsigned char *image) {
	// create and load texture raster
	int nchars = (int) strlen(lowerCaseImage), npixels = nchars/2, height = 13, width = npixels/height;
	unsigned char *pixels = new unsigned char[3*npixels], *p = pixels, *n = (unsigned char *) image;
	for (int i = 0; i < npixels; i++) {
		char c1 = *n++, c2 = *n++;
		int k1 = c1 < 58? c1-'0' : 10+c1-'A', k2 = c2 < 58? c2-'0' : 10+c2-'A', b = 16*k1+k2;
		for (int k = 0; k < 3; k++)
			*p++ = (unsigned char) b;
	}
	int textureName = LoadTexture(pixels, width, height, 3);
	delete [] pixels;
	return textureName;
}

int MakeNumberTexture(unsigned char *image) {
	// create and load texture raster
	int nchars = (int) strlen(numberImage), npixels = nchars/2, height = 10, width = npixels/height;
	unsigned char *pixels = new unsigned char[3*npixels], *p = pixels, *n = (unsigned char *) image;
	for (int i = 0; i < npixels; i++) {
		char c1 = *n++, c2 = *n++;
		int k1 = c1 < 58? c1-'0' : 10+c1-'A', k2 = c2 < 58? c2-'0' : 10+c2-'A', b = 16*k1+k2;
		for (int k = 0; k < 3; k++)
			*p++ = (unsigned char) b;
	}
	int textureName = LoadTexture(pixels, width, height, 3);
	delete [] pixels;
	return textureName;
}

void Letter(int x, int y, char c, vec3 color, float ptSize) {
	if (c < 48 || c == 61 || c == 94) { // 32(space), 40((), 41()), 43(+), 45(-), 46(.), 47(/), 61(=), 94(^)
		float lineWidth = 4; // ptSize/3; // = 2;
		UseDrawShader(ScreenMode());
		int size = (int) ptSize, h = (int)(ptSize*.5f), hh = (int)(ptSize*.75f);
		if (c == 40) {
			vec2 p1(x+h, y+size+1), p2(x+2, y+(int)(.75f*ptSize)), p3(x+2, y+(int)(.25f*ptSize)), p4(x+h, y-1);
			Line(p1, p2, lineWidth, color); Line(p2, p3, lineWidth, color); Line(p3, p4, lineWidth, color);
		}
		if (c == 41) {
			vec2 p1(x+h, y+size+1), p2(x+size-2, y+(int)(.75f*ptSize)), p3(x+size-2, y+(int)(.25f*ptSize)), p4(x+h, y-1);
			Line(p1, p2, lineWidth, color); Line(p2, p3, lineWidth, color); Line(p3, p4, lineWidth, color);
		}
		if (c == 61) {
			Line(x+1, y+h+3, x+h+6, y+h+3, lineWidth, color);
			Line(x+1, y+h-3, x+h+6, y+h-3, lineWidth, color);
		}
		if (c == 43) {
			Line(x+1, y+h+1, x+h+6, y+h+1, lineWidth, color);
			Line(x+h, y+2, x+h, y+h+6, lineWidth, color);
		}
		if (c == 45) Line(x+1, y+h, x+h+3, y+h, lineWidth, color);
		if (c == 46) Disk(vec2(x+h, y+3), ptSize/3, color);
		if (c == 47) Line(x+1, y, x+size-1, y+size, lineWidth, color);
		if (c == 94) {
			Line(x+1, y+2, x+h, y+h+4, lineWidth, color);
			Line(x+h, y+h+4, x+size-2, y+2, lineWidth, color);
		}
		return;
	}
	enum { Upper, Lower, Number, Unknown } type =
		c >= 65 && c <= 90?  Upper  :
		c >= 97 && c <= 122? Lower  :
		c >= 48 && c <= 57?  Number :
							 Unknown;
	if (type == Unknown)
		return;
	if (!textureNameLower)
		textureNameLower = MakeLetterTexture((unsigned char *) lowerCaseImage);//, textureUnitLower);
	if (!textureNameUpper)
		textureNameUpper = MakeLetterTexture((unsigned char *) upperCaseImage);//, textureUnitUpper);
	if (!textureNameNumber)
		textureNameNumber = MakeNumberTexture((unsigned char *) numberImage);//, textureUnitNumber);
	if (!textureNameLower || !textureNameUpper || !textureNameNumber)
		printf("can't make texture maps\n");
	if (!shaderProgram)
		shaderProgram = LinkProgramViaCode(&vertexShader, &pixelShader);
	glUseProgram(shaderProgram);
	if (!vBufferId) {
		glGenBuffers(1, &vBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*6, NULL, GL_DYNAMIC_DRAW);
			// need 4 vertices for quad, but 6 if triangles
	}
	glBindBuffer(GL_ARRAY_BUFFER, vBufferId);
	VertexAttribPointer(shaderProgram, "point", 4, 4*sizeof(float), 0);
		// each vertex is 4 floats, stride is 4 floats
	int texUnit = type == Upper? textureUnitUpper : type == Lower? textureUnitLower : textureUnitNumber;
	GLuint texName = type == Upper? textureNameUpper : type == Lower? textureNameLower : textureNameNumber;
	glActiveTexture(GL_TEXTURE0+texUnit);
	glBindTexture(GL_TEXTURE_2D, texName);
	// set screen-mode
	SetUniform(shaderProgram, "view", ScreenMode());
	// set text color and texture map, activate texture
	SetUniform(shaderProgram, "color", color);
	SetUniform(shaderProgram, "textureImage", texUnit);
	// enable blended overwrite of color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// display character c, value determines horizontal position along texture
	float w = .8f*ptSize, h = ptSize, xx = (float) x, yy = (float) y;
	float t = 0, dt = 0;
	if (type == Number) {
		int value = c-'0';
		dt = 1.f/10.f; t = (float) value*dt;
		float vertices[][4] = { {xx, yy, t, 1}, {xx+w, yy, t+dt, 1}, {xx+w, yy+h, t+dt, 0}, {xx, yy+h, t, 0} };
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	}
	else {
		int letterID = type == Upper? c-'A' : type == Lower? c-'a' : c-'0';
		dt = 1.f/26.f; t = (float)letterID*dt;
	//	float vertices[][4] = { {xx, yy+h, t, 1}, {xx+w, yy+h, t+dt, 1}, {xx+w, yy, t+dt, 0}, {xx, yy, t, 0} };
		float vertices[][4] = { {xx, yy, t, 1}, {xx+w, yy, t+dt, 1}, {xx+w, yy+h, t+dt, 0}, {xx, yy+h, t, 0} };
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	}
	// display as one quad or two triangles, mapped to 1/26 width of texture map
#ifndef __APPLE__
	glDrawArrays(GL_QUADS, 0, 4);
#else
	float vertices[][4] = {{xx, yy, t, 1}, {xx+w, yy, t+dt, 1},   {xx+w, yy+h, t+dt, 0},
					       {xx, yy, t, 1}, {xx+w, yy+h, t+dt, 0}, {xx, yy+h, t, 0}};
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Letters(int x, int y, const char *letters, vec3 color, float ptSize) {
	int was = 0;
	mat4 drawView = GetDrawView();
	glGetIntegerv(GL_CURRENT_PROGRAM, &was);
	for (int i = 0; i < (int) strlen(letters); i++)
		Letter((int) (x+i*ptSize), y, letters[i], color, ptSize);
	glUseProgram(was);
	SetDrawView(drawView);
}

void Letters(vec3 p, mat4 m, const char *letters, vec3 color, float ptSize) {
	int was = 0;
	mat4 drawView = GetDrawView();
	glGetIntegerv(GL_CURRENT_PROGRAM, &was);
	vec2 pp = ScreenPoint(p, m);
	for (int i = 0; i < (int) strlen(letters); i++)
	//	Letter((int) (pp.x+i*10.9f), (int) pp.y, letters[i], color, ptSize);
		Letter((int) (pp.x+i*ptSize), (int) pp.y, letters[i], color, ptSize);
	glUseProgram(was);
	SetDrawView(drawView);
}

/*	// method to convert image to hexadecimal data
	const char *filename = "C:/Users/Jules/Code/Aids/LowerCase.tga";
	int width, height, bytesPerPixel;
	unsigned char *pixels = ReadTarga(filename, &width, &height, &bytesPerPixel);
	unsigned char *p = pixels;
	const char *hexa = "0123456789ABCDEF";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++, p += 3) {
			int n = (int) *p;
			int k1 = n/16, k2 = n-(16*k1);
			printf("%c%c", hexa[k1], hexa[k2]);
		}
		printf("\\\n");
	} */
