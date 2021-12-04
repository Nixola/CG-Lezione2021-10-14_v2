#include "HermiteCurve.h"

#include <iostream>

glm::vec2 Spite::HermiteCurve::derivative(int i, float Tens, float Bias, float Cont)
{
	float step = 1.f / (float)(_controlPoints.size() - 1);
	int next = i + 1;
	//float x, y;
	glm::vec2 point;
	if (i == 0) {
		point = 0.5f * (1.f - Tens) * (1.f - Bias) * (1.f - Cont) * (_controlPoints[i + 1] - _controlPoints[i]) / step;
		//x = 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i + 1].x - _controlPoints[i].x) / step;
		//y = 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i + 1].y - _controlPoints[i].y) / step;
	} else if (i == _controlPoints.size() - 1) {
		point = 0.5f * (1.f - Tens) * (1.f - Bias) * (1.f - Cont) * (_controlPoints[i] - _controlPoints[i - 1]) / step;
		//x = 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i].x - _controlPoints[i - 1].x) / step;
		//y = 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i].y - _controlPoints[i - 1].y) / step;
	} else if (i % 2 == 0) {
		point = 0.5f * (1.f - Tens) * (1.f + Bias) * (1.f + Cont) * (_controlPoints[i] - _controlPoints[i - 1]) / step + 0.5f * (1.f - Tens) * (1.f - Bias) * (1.f - Cont) * (_controlPoints[next] - _controlPoints[i]) / step;
		//x = 0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 + Cont) * (_controlPoints[i].x - _controlPoints[i - 1].x) / step + 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i + 1].x - _controlPoints[i].x) / step;
		//y = 0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 + Cont) * (_controlPoints[i].y - _controlPoints[i - 1].y) / step + 0.5 * (.01 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (_controlPoints[i + 1].y - _controlPoints[i].y) / step;
	}
	else {
		point = 0.5f * (1.f - Tens) * (1.f + Bias) * (1.f - Cont) * (_controlPoints[i] - _controlPoints[i - 1]) / step + 0.5f * (1.f - Tens) * (1.f - Bias) * (1.f + Cont) * (_controlPoints[next] - _controlPoints[i]) / step;
		//x = 0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 - Cont) * (_controlPoints[i].x - _controlPoints[i - 1].x) / step + 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 + Cont) * (_controlPoints[i + 1].x - _controlPoints[i].x) / step;
		//y = 0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 - Cont) * (_controlPoints[i].y - _controlPoints[i - 1].y) / step + 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 + Cont) * (_controlPoints[i + 1].y - _controlPoints[i].y) / step;
	}
	return point;
}
glm::vec2 Spite::HermiteCurve::derivative(int i)
{
	return derivative(i, 0, 0, 0);
}

Spite::HermiteCurve::HermiteCurve(std::vector<glm::vec2>& points, int segments, GLuint hint) : HermiteCurve(segments, hint)
{
	_controlPoints = points;
}

Spite::HermiteCurve::HermiteCurve(int segments, GLuint hint) : Drawable(segments, hint)
{
	_segments = segments;
}

//void InterpolazioneHermite(float* t, Figura* Fig, vec4 color_top, vec4 color_bot)
void Spite::HermiteCurve::interpolate(glm::vec4 color)
{
	float p_t = 0, p_b = 0, p_c = 0;
	float passotg = 1.0 / (float) (_segments - 1.f);

	float tg = 0, tgmapp, ampiezza;
	int i = 0;
	int is = 0; //indice dell'estremo sinistro dell'intervallo [t(i),t(i+1)] a cui il punto tg
				//appartiene

	_vertexData.clear();

	for (tg = 0; tg <= 1; tg += passotg)
	{
		if (tg > (float) (is+1) / (float) (_controlPoints.size() - 1)) is++;

		ampiezza = 1.f / (float)(_controlPoints.size() - 1);
		tgmapp = (tg - (float)is / (float)(_controlPoints.size() - 1)) / ampiezza;

		glm::vec2 point = _controlPoints[is] * (float) PHI0(tgmapp) + derivative(is) * (float) PHI1(tgmapp) * ampiezza + _controlPoints[is + 1] * (float) PSI0(tgmapp) + derivative(is + 1) * PSI1(tgmapp) * ampiezza;
		_vertexData.push_back({ glm::vec3(point, 0.0), color, glm::vec2(0.0) }); // TODO: overwrite, not recreate
	}

}