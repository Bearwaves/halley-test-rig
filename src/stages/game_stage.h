#pragma once

#include <halley.hpp>
#include <memory>

using namespace Halley;

class GameStage : public Stage
{
public:
	void init() override;
	void onFixedUpdate(Time t) override;
	void onVariableUpdate(Time t) override;
	void onRender(RenderContext& rc) const override;
private:
	float r, g, b;
	Sprite background;
	Sprite halleyLogo;
	std::unique_ptr<TextureRenderTarget> gameCanvasTarget;
};
