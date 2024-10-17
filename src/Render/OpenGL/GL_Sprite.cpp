#include "glad/glad.h"
#include "Render/Sprite.h"

ASprite::ASprite(const std::shared_ptr<ATexture> pTexture, const std::shared_ptr<AShaderProgram> pShaderProgram) : m_pTexture(pTexture), m_pShaderProgram(pShaderProgram)
{
	const GLfloat points[] =
	{
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,

		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
	};

	const GLfloat texCoords[] =
	{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vertexCoordsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


	glGenBuffers(1, &m_textureCoordsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), &texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ASprite::~ASprite()
{
	glDeleteBuffers(1, &m_vertexCoordsVBO);
	glDeleteBuffers(1, &m_textureCoordsVBO);
	glDeleteVertexArrays(1, &m_vao);
}

void ASprite::Render(AMat4x4& projMat, AMat4x4& modelMat)
{
	glBindVertexArray(m_vao);
	m_pShaderProgram->SetMatrix4("modelMat", modelMat);
	m_pShaderProgram->SetMatrix4("projectionMat", projMat);

	glActiveTexture(GL_TEXTURE0);
	m_pTexture->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
