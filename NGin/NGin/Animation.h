#pragma once
class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, int nFrames, float holdTime)
		:
		holdTime(holdTime)
	{
		frames.reserve(nFrames);
		pTex = TextureCodex::Acquire("professor_walk_cycle_no_hat.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames.emplace_back(sf::Vector2i{ x,y }, sf::Vector2i{ width,height });
			x += width;
		}
	}
	void ApplyToSprite(sf::Sprite& s) const
	{
		s.setTexture(*pTex);
		s.setTextureRect(frames[iFrame]);
	}
	void Update(float dt)
	{
		time += dt;
		while (time >= holdTime)
		{
			time -= holdTime;
			Advance();
		}
	}
private:
	void Advance()
	{
		if (++iFrame >= int(frames.size()))
		{
			iFrame = 0;
		}
	}
private:
	float holdTime;
	std::shared_ptr<sf::Texture> pTex;
	std::vector<sf::IntRect> frames;
	int iFrame = 0;
	float time = 0.0f;
};