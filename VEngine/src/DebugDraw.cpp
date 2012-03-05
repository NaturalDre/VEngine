#include <vengine\DebugDraw.h>
#include <vengine\Physics.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <vengine\Utility.h>

#define USE_OLD_DEBUG_DRAWER
#define DISABLE_CONVERT_ALLEGRO_COORDS_TO_OPENGL

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
#ifndef DISABLE_INVERT
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(-vertices[i]));
#else
		b2Vec2 vert = VE::getScreenPos(vertices[i]);
#endif
		glVertex2f(vert.x, vert.y);
	}
	glEnd();

}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
#ifndef USE_OLD_DEBUG_DRAWER


#else
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(vertices[i]));
#ifndef DISABLE_CONVERT_ALLEGRO_COORDS_TO_OPENGL
		vert.y += al_get_display_height(al_get_current_display()) - (vert.y * 2);
#endif
		glVertex2f(vert.x, vert.y);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(vertices[i]));
#ifndef DISABLE_CONVERT_ALLEGRO_COORDS_TO_OPENGL
		vert.y += al_get_display_height(al_get_current_display()) - (vert.y * 2);
#endif
		glVertex2f(vert.x, vert.y);
	}
	glEnd();

#endif
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
#ifndef USE_OLD_DEBUG_DRAWER
	b2Vec2 v = VE::mtrToPix(center);
	ALLEGRO_COLOR col = al_map_rgb(color.r, color.g, color.b);
	col.a = 0.7;
	al_draw_circle(center.x, center.y, VE::mtrToPix(radius), col, 1);
#else
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(v));
		glVertex2f(vert.x, vert.y);
		theta += k_increment;
	}
	glEnd();
#endif
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
#ifndef USE_OLD_DEBUG_DRAWER
	ALLEGRO_STATE state;
	//al_store_state(&state, ALLEGRO_STATE_BLENDER);
	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_DEST_MINUS_SRC);
	b2Vec2 v = center;
	v = VE::getScreenPos(center);
	ALLEGRO_COLOR col = al_map_rgb(color.r, color.g, color.b);
	col.a = 0.7f;
	al_draw_filled_circle(v.x,v.y, VE::mtrToPix(radius), col);
	//al_restore_state(&state);
#else

	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(v));
		glVertex2f(vert.x, vert.y);
		theta += k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		b2Vec2 vert = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(v));
		glVertex2f(vert.x, vert.y);
		theta += k_increment;
	}
	glEnd();

	b2Vec2 p = center + radius * axis;
	glBegin(GL_LINES);
	b2Vec2 cent = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(center));
	glVertex2f(cent.x, cent.y);
	b2Vec2 pv = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p));
	glVertex2f(pv.x, pv.y);
	glEnd();
#endif
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
		//glColor3f(color.r, color.g, color.b);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	b2Vec2 vert1 = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p1));
	glVertex2f(vert1.x, vert1.y);
	b2Vec2 vert2 = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p2));
	glVertex2f(vert2.x, vert2.y);
	glEnd();
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	glBegin(GL_LINES);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	b2Vec2 pos1 = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p1));
	glVertex2f(pos1.x, pos1.y);
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	b2Vec2 pos2 = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p2));
	glVertex2f(pos2.x, pos2.y);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(pos1.x, pos1.y);
	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	pos2 = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p2));
	glVertex2f(pos2.x, pos2.y);

	glEnd();
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	b2Vec2 point = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(p));
	glVertex2f(point.x, point.y);
	glEnd();
	glPointSize(1.0f);
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf_s(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = 800;
	int h = 600;
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//glColor3f(0.9f, 0.6f, 0.6f);
	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y); ////
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_LINE_LOOP);
	b2Vec2 lB = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(aabb->lowerBound));
	b2Vec2 uB = VE::Utility::GameToScreenPosPix(VE::Utility::mtrToPix(aabb->upperBound));
	glVertex2f(lB.x, lB.y);
	glVertex2f(uB.x,lB.y);
	glVertex2f(uB.x, uB.y);
	glVertex2f(lB.x, uB.y);
	glEnd();
}