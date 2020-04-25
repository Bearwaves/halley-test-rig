#include "game_stage.h"
#include <memory>

void GameStage::init()
{
	r = 0.1f;
	g = 0.7f;
	b = 0.4f;
	auto mat = std::make_shared<Material>(getResource<MaterialDefinition>("Halley/Scanlines"));
	mat
			->set("u_col0", Colour4f(0.08f))
			.set("u_col1", Colour4f(0.07f))
			.set("u_distance", 6.0f);
	background = Sprite().setMaterial(mat).setPos(Vector2f(0, 0));

	auto col = Colour4f(0.065f);
	halleyLogo = Sprite()
			.setImage(getResources(), "halley/halley_icon_dist.png", "Halley/DistanceFieldSprite")
			.setPivot(Vector2f(0.5f, 0.5f))
			.setColour(col)
			.setScale(Vector2f(8, 8))
			.setPos(Vector2f(640, 360));
	halleyLogo.getMaterial()
			.set("u_smoothness", 0.125f)
			.set("u_outline", 0.0f)
			.set("u_outlineColour", col);

		auto textureSize = Vector2i(1280, 720);
		std::shared_ptr<Texture> tex = getVideoAPI().createTexture(textureSize);
		auto desc = TextureDescriptor(textureSize, TextureFormat::RGBA);
		desc.isRenderTarget = true;
		tex->load(std::move(desc));

		gameCanvasTarget = getVideoAPI().createTextureRenderTarget();
		gameCanvasTarget->setTarget(0, tex);
		gameCanvasTarget->setViewPort(Rect4i(Vector2i(), Vector2i(1280, 720)));
}

void GameStage::onFixedUpdate(Time t)
{
}

void GameStage::onVariableUpdate(Time t)
{
	r = fmod(r + t, 1);
	g = fmod(g + t, 1);
	b = fmod(b + t, 1);
}

void GameStage::onRender(RenderContext& rc) const
{
	rc.with(*gameCanvasTarget).bind([&](Painter& painter) {

		auto view = Rect4f(painter.getViewPort());
		Sprite bg = background;
		bg.getMaterial().set("u_col0", Colour4f(r, g, b, 1));
		bg.setTexRect(view).setSize(view.getSize()).draw(painter);

		halleyLogo.clone().setPos(Vector2f(view.getSize() / 2)).draw(painter);
	});

	rc.bind([&](Painter& painter){
		auto tex = gameCanvasTarget->getTexture(0);
		Sprite()
			.setPos(Vector2f())
			.setScale(0.5f)
			.setImage(tex, getResource<MaterialDefinition>("Halley/SpriteOpaque"))
			.draw(painter);
		Sprite()
			.setPos(Vector2f(640, 360))
			.setScale(0.5f)
			.setImage(tex, getResource<MaterialDefinition>("Halley/SpriteOpaque"))
			.draw(painter);
	});
}
