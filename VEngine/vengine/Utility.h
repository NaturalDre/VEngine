#ifndef UTILITY_H
#define UTILITY_H

#include <allegro5\allegro5.h>
#include <string>
#include <Box2D\Box2D.h>
#include <vector>
#include <lua.hpp>

namespace VE
{
	namespace Utility
	{
		// Helper function to report an error to the user.
		void ReportError(const std::string& msg, const std::string& errorTitle = "An error has occured.", const std::string& windowTitle = "Error");
		/*
		 *	StripFilename()
		 *
		 *	Get the filename and extension from the full directory.
		 *	E.G.: Pass C:\Hello.lua and the function returns Hello.lua
		 *
		 *	Params:
		 *		const std::string: The full directory link
		 *
		 *	Returns: std::string: The stripped name and extension
		 *
		 */
		std::string StripFilename(const std::string&  filename);	
		/*
		 *	GetColRow()
		 *
		 *	Which (Col,Row) would ID be in a grid with this many columns?
		 *
		 *	Params:
		 *		size_t cols: How many columns are there?
		 *		size_t id: What position?
		 *
		 *	Notes:
		 *		As an example, If there is a grid with 10 columns and you want
		 *		to find out what element(left->right, next row, left->right, etc)
		 *		element 14 would be, you should do GetColRow(10, 14). Which would
		 *		return b2Vec2(4, 2).  Column 4, Row 2.
		 */
		b2Vec2 GetColRow(size_t cols, size_t id);
		/*
		 *	FileToBuffer()
		 *	
		 *	Buffers a file's contents into a vector of characters.
		 *
		 *	Params:
		 *		const std::string filename: The filename and location of the file.
		 *
		 *	Notes:
		 *		A character on the system must be equal to 1 byte.
		 *		This function uses PHYSFS to load and buffer the file.
		 *		This means if you do not put the directory that this file
		 *		is in into PHYSFS' search path, it will not be found and
		 *		and the function will return an empty buffer.
		 */
		std::vector<char> FileToBuffer(const std::string filename);
		/*
		 *	L_BufferAndLoad
		 *
		 *	Buffers an lua script file's contents into a vector of characters, loads 
		 *	and executes it in the passed lua_State and then frees the buffer.
		 *
		 *	Params:
		 *		const std::string& filename: The filename and location of the lua script.
		 *		lua_State* L: The lua_State to execute the script in. Must not be null.
		 *
		 *	Returns: bool: True if operation succeeded. False otherwise.
		 *
		 *	Throws:
		 */
		bool L_BufferAndLoad(const std::string& filename, lua_State* L);

		// ALLEGRO_EVENT_QUEUE delete functor
		struct AlQueueDel
		{
			void operator()(ALLEGRO_EVENT_QUEUE* ptr) const { al_destroy_event_queue(ptr); ptr = nullptr; }
		};
		// ALLEGRO_TIMER delete functor
		struct AlTimerDel
		{
			void operator()(ALLEGRO_TIMER* ptr) const { al_destroy_timer(ptr); ptr = nullptr; }
		};
		// ALLEGRO_MUTEX delete functor
		struct AlMutexDel
		{
			void operator()(ALLEGRO_MUTEX* ptr)  const { al_destroy_mutex(ptr); ptr = nullptr; }
		};
		// b2Body delete functor
		struct b2BodyDtor
		{
			void operator()(b2Body* body);
		};
	}
}
#endif