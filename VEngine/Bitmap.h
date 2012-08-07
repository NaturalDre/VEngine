#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include "Physics.h"

struct ALLEGRO_BITMAP;

namespace VE
{
	class CBitmap
	{
	public:
		/// Load a bitmap from a file.
		explicit CBitmap(const std::string& filename = "");
		// Create a sub bitmap. Note: You must free the parent before this is deleted.
		CBitmap(const CBitmap& parent, size_t x, size_t y, size_t w, size_t h);
		// Take ownership of this ALLEGRO_BITMAP
		explicit CBitmap(ALLEGRO_BITMAP* bitmap);
		// Copy
		CBitmap(const CBitmap& rhs); 
		// Move Copy
		CBitmap(CBitmap&& rhs);
		// Assignment
		const CBitmap& operator=(const CBitmap& rhs);
		// Move Assignment
		const CBitmap& operator=(CBitmap&& rhs);
		//
		operator bool() const { return IsValid(); }

		~CBitmap(void);

		//std::shared_ptr<CBitmap> CreateSubBitmap(size_t x, size_t y, size_t w, size_t h);

		void Reset(void);

		/**
		* \return Width in pixels.
		*/
		size_t GetWidth(void) const;
		/**
		* \return Height in pixels.
		*/
		size_t GetHeight(void) const; /// Pixels
		ALLEGRO_BITMAP* GetRaw(void) const;
		/**
		* \return True if this bitmap is valid and usable. False if not.
		*/
		bool IsValid(void) const;
		/**
		* \return True if this bitmap is a subbitmap. False otherwise.
		*/
		bool IsSubBitmap(void) const;
		/**
		* \return Whether or not the bitmap is locked.
		*/
		bool IsLocked(void) const;
		/**
		* \return The flags used to create the bitmap.
		*/
		int GetFlags(void) const; 
		/**
		* \return  The pixel format of the bitmap.
		* \note See Allegro Manual: ALLEGRO_PIXEL_FORMAT
		*/
		int GetFormat(void) const;
		//
		void ConvertMaskToAlpha(size_t r, size_t g, size_t b);
	private:
		class Bitmap;
		Bitmap* d; // Implementation of the bitmap.
	};

	bool IsDrawable(const CBitmap& bitmap, b2Vec2 bitmapPos, b2Vec2 bitmapCPos = b2Vec2(0,0));
	/**
	* Draw a bitmap to the screen using game world coordinates.
	*
	* @param bitmap The bitmap to draw.
	* @param pos The position on the screen to draw at in meters.
	* @param flags Rules to apply to bitmap drawing. 
	*	ALLEGRO_FLIP_HORIZONTAL, ALLEGRO_FLIP_VERTICAL.
	* @note The top left of the bitmap is considered the origin(0,0).
	*/
	void DrawBitmap(const CBitmap& bitmap, b2Vec2 dpos, int flags = 0);
	/**
	* Draw a rotated bitmap to the screen using world
	* @param bitmap The bitmap to draw.
	* @param dpos The position on the screen to draw at in meters.
	* @param cpos The center of the bitmap in local coordinates. By default
	*	the center is also the origin(0,0) therefore if a bitmap is 30 x 30 its
	*	center is represented as (0,0) in Box2D, not (15,15) like you'd expect.
	*	This is necessary due to how Box2D works.
	* @param flags Rules to apply to bitmap drawing. 
	*	ALLEGRO_FLIP_HORIZONTAL, ALLEGRO_FLIP_VERTICAL.
	*/
	void DrawBitmap(const CBitmap& bitmap, b2Vec2 dpos, b2Vec2 cpos, float angle = 0.0f, int flags = 0);
}


#endif