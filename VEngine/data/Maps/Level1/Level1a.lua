map = { version = "1.1", luaversion = "5.1", orientation = "orthogonal", width = 100, height = 30, tilewidth = 64, tileheight = 64, properties = {}, tilesets = { { name = "blocksheet", firstgid = 1, tilewidth = 64, tileheight = 64, spacing = 0, margin = 0, image = "Tilesets/blocksheet.png", imagewidth = 384, imageheight = 128, properties = {}, tiles = {} }, { name = "Corners-1", firstgid = 13, tilewidth = 64, tileheight = 64, spacing = 0, margin = 0, image = "Tilesets/Corners-1.png", imagewidth = 384, imageheight = 128, properties = {}, tiles = {} }, { name = "Corners-2_90CW", firstgid = 25, tilewidth = 64, tileheight = 64, spacing = 0, margin = 0, image = "Tilesets/Corners-2_90CW.png", imagewidth = 128, imageheight = 384, properties = {}, tiles = {} }, { name = "Corners-3_180CW", firstgid = 37, tilewidth = 64, tileheight = 64, spacing = 0, margin = 0, image = "Tilesets/Corners-3_180CW.png", imagewidth = 384, imageheight = 128, properties = {}, tiles = {} }, { name = "Corners-4_270CW", firstgid = 49, tilewidth = 64, tileheight = 64, spacing = 0, margin = 0, image = "Tilesets/Corners-4_270CW.png", imagewidth = 128, imageheight = 384, properties = {}, tiles = {} } }, layers = { { type = "tilelayer", name = "Tile Layer 1", x = 0, y = 0, width = 100, height = 30, visible = true, opacity = 1, properties = {}, encoding = "lua", data = { 1, 9, 6, 2, 7, 4, 8, 10, 2, 8, 1, 4, 9, 2, 6, 10, 3, 5, 7, 7, 9, 11, 10, 7, 3, 3, 9, 12, 4, 10, 9, 1, 11, 2, 7, 6, 1, 12, 7, 6, 7, 12, 3, 2, 11, 3, 10, 4, 8, 6, 2, 5, 8, 5, 10, 3, 9, 10, 3, 11, 2, 7, 2, 6, 4, 12, 6, 12, 5, 6, 11, 1, 6, 4, 3, 5, 6, 2, 10, 8, 7, 7, 10, 9, 6, 3, 2, 3, 8, 9, 11, 9, 5, 5, 3, 9, 8, 5, 5, 6, 1, 6, 7, 11, 4, 5, 5, 5, 4, 7, 1, 3, 6, 4, 5, 12, 9, 1, 6, 3, 5, 1, 4, 7, 1, 12, 3, 2, 2, 2, 2, 3, 4, 3, 4, 2, 7, 9, 1, 2, 9, 2, 12, 10, 10, 8, 11, 11, 5, 6, 1, 3, 6, 2, 10, 7, 10, 3, 6, 1, 8, 4, 12, 11, 11, 11, 10, 5, 10, 9, 9, 10, 11, 5, 5, 10, 3, 6, 2, 10, 1, 8, 8, 7, 5, 10, 10, 5, 9, 5, 12, 3, 12, 2, 7, 5, 5, 5, 3, 9, 11, 6, 10, 2, 3, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 6, 12, 10, 1, 1, 11, 3, 10, 10, 9, 8, 7, 5, 5, 6, 5, 5, 10, 11, 3, 10, 7, 5, 2, 3, 12, 4, 9, 12, 12, 4, 8, 12, 9, 4, 12, 7, 1, 7, 3, 1, 2, 2, 8, 3, 7, 12, 5, 4, 4, 6, 11, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 7, 1, 5, 12, 1, 7, 11, 6, 5, 7, 12, 12, 8, 8, 4, 11, 5, 4, 3, 6, 1, 10, 5, 5, 7, 5, 8, 9, 11, 11, 9, 1, 3, 1, 2, 5, 1, 9, 6, 6, 1, 2, 6, 8, 4, 11, 7, 8, 6, 7, 1, 12, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 5, 1, 7, 7, 5, 6, 2, 7, 7, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 7, 2, 7, 6, 3, 3, 3, 11, 3, 11, 3, 8, 8, 1, 6, 6, 11, 10, 10, 2, 10, 12, 9, 6, 3, 1, 3, 12, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 10, 4, 8, 11, 0, 0, 6, 10, 3, 9, 1, 1, 7, 3, 3, 6, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 7, 4, 2, 12, 10, 4, 5, 12, 1, 2, 11, 0, 0, 0, 0, 0, 0, 0, 3, 9, 5, 6, 1, 8, 5, 10, 4, 8, 10, 6, 2, 10, 7, 12, 12, 5, 1, 12, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 5, 11, 12, 6, 12, 10, 9, 3, 0, 0, 0, 0, 0, 0, 0, 12, 10, 12, 3, 5, 10, 4, 8, 10, 1, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 4, 9, 11, 8, 2, 1, 4, 9, 5, 1, 5, 11, 1, 4, 1, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 7, 0, 0, 4, 5, 2, 0, 0, 0, 0, 0, 0, 0, 11, 5, 9, 3, 9, 11, 2, 2, 8, 6, 4, 0, 0, 0, 0, 4, 2, 0, 0, 1, 11, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 12, 1, 11, 5, 6, 10, 12, 8, 9, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 7, 5, 0, 0, 1, 0, 0, 9, 10, 6, 4, 6, 10, 9, 2, 0, 0, 0, 0, 6, 1, 3, 2, 11, 7, 0, 0, 0, 0, 0, 0, 12, 1, 11, 0, 0, 8, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 11, 0, 0, 0, 0, 0, 0, 0, 2, 11, 11, 7, 2, 9, 1, 9, 2, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 8, 8, 0, 0, 11, 0, 0, 3, 1, 10, 9, 6, 7, 11, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 10, 0, 0, 7, 4, 8, 5, 12, 3, 4, 1, 5, 11, 6, 4, 5, 5, 8, 3, 10, 8, 0, 0, 0, 0, 0, 0, 0, 9, 9, 10, 6, 6, 8, 12, 11, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 12, 9, 9, 9, 8, 7, 10, 4, 10, 6, 10, 9, 3, 2, 5, 1, 9, 5, 2, 0, 0, 6, 0, 0, 8, 1, 1, 4, 5, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 2, 12, 1, 11, 1, 3, 7, 8, 0, 0, 0, 0, 0, 0, 0, 12, 7, 11, 4, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 5, 9, 12, 6, 7, 6, 6, 3, 6, 8, 0, 0, 2, 0, 0, 8, 11, 7, 8, 8, 11, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 9, 12, 9, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 10, 6, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 8, 10, 6, 4, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 3, 9, 12, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 11, 2, 11, 11, 3, 5, 4, 11, 6, 11, 4, 3, 7, 1, 5, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 10, 10, 6, 6, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 3, 3, 9, 4, 8, 11, 3, 10, 12, 1, 9, 6, 12, 9, 4, 3, 11, 2, 9, 7, 7, 13, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 4, 7, 7, 3, 9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 11, 0, 0, 0, 0, 0, 0, 0, 5, 7, 1, 12, 12, 7, 3, 7, 12, 4, 2, 7, 8, 3, 3, 9, 5, 12, 1, 2, 2, 3, 6, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 8, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 5, 9, 3, 6, 1, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 12, 7, 4, 9, 4, 3, 3, 7, 8, 6, 3, 4, 4, 11, 7, 4, 2, 9, 10, 26, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 6, 11, 3, 1, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 1, 2, 10, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 6, 5, 2, 9, 10, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 4, 1, 10, 4, 9, 6, 11, 11, 12, 12, 9, 5, 12, 1, 9, 12, 11, 11, 6, 2, 10, 3, 8, 8, 11, 11, 2, 12, 3, 4, 11, 6, 8, 0, 0, 0, 0, 0, 0, 0, 5, 11, 9, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 12, 1, 9, 4, 12, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 12, 7, 4, 6, 7, 5, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 10, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 1, 6, 4, 6, 8, 8, 12, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 11, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 12, 7, 6, 12, 7, 7, 6, 9, 11, 6, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 11, 7, 5, 5, 1, 5, 3, 7, 6, 2, 3, 11, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 11, 2, 3, 1, 2, 3, 4, 5, 6, 21, 0, 0, 0, 0, 0, 0, 56, 3, 4, 5, 6, 1, 2, 3, 0, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 11, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 3, 7, 5, 8, 6, 5, 2, 4, 11, 2, 7, 7, 8, 9, 10, 11, 12, 7, 0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 2, 12, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 10, 8, 4, 10, 11, 10, 2, 11, 5, 5, 10, 1, 2, 3, 4, 5, 6, 1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 10, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 3, 7, 7, 9, 12, 1, 11, 11, 10, 4, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 1, 6, 8, 5, 9, 4, 12, 6, 5, 2, 2, 3, 12, 3, 12, 11, 1, 12, 6, 8, 11, 10, 4, 8, 7, 10, 7, 6, 3, 9, 1, 4, 3, 11, 6, 8, 7, 2, 7, 10, 10, 7, 10, 7, 2, 10, 3, 5, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 3, 10, 7, 1, 6, 11, 1, 3, 11, 9, 5, 7, 3, 9, 5, 6, 11, 3, 11, 3, 8, 7, 10, 5, 8, 5, 1, 9, 7, 10, 11, 5, 10, 2, 8, 1, 3, 4, 11, 5, 5, 7, 7, 4, 10, 1, 3, 2, 3, 10, 2, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 11, 12, 7, 6, 8, 10, 7, 4, 3, 11, 8, 6, 9, 12, 8, 5, 3, 5, 6, 4, 8, 3, 3, 2, 5, 2, 4, 7, 4, 11, 1, 7, 10, 6, 10, 2, 11, 5, 6, 9, 9, 6, 9, 10, 6, 1, 3, 2, 9, 3, 6, 7, 2 } }, { type = "objectgroup", name = "Main Gameplay", visible = true, opacity = 1, properties = {}, objects = { { name = "", type = "Player", x = 2038, y = 833, width = 64, height = 128, properties = {} }, { name = "Harpoon1", type = "Harpoon", x = 1600, y = 1024, width = 384, height = 64, properties = { ["direction"] = "left", ["speed"] = "5" } }, { name = "Platform1", type = "Elevator", x = 1280, y = 1600, width = 320, height = 320, properties = { ["isAuto"] = "false", ["lowerLimit"] = "-20", ["upperLimit"] = "0" } }, { name = "", type = "Box", x = 1038, y = 1402, width = 64, height = 64, properties = {} }, { name = "fdsfsdaf", type = "BlockPlatform", x = 512, y = 1408, width = 384, height = 64, properties = {} }, { name = "area_blockPlat1", type = "Area", x = 64, y = 1216, width = 192, height = 128, properties = {} }, { name = "bl_plat1", type = "BlockPlatform", x = 1600, y = 1152, width = 704, height = 64, properties = {} }, { name = "bl_plat2", type = "BlockPlatform", x = 1600, y = 1216, width = 640, height = 64, properties = {} }, { name = "bl_plat3", type = "BlockPlatform", x = 1664, y = 1280, width = 512, height = 64, properties = {} }, { name = "bl_plat4", type = "BlockPlatform", x = 1600, y = 1344, width = 512, height = 64, properties = {} }, { name = "bl_plat5", type = "BlockPlatform", x = 1600, y = 1408, width = 448, height = 64, properties = {} }, { name = "bl_plat6", type = "BlockPlatform", x = 1600, y = 1472, width = 256, height = 64, properties = {} }, { name = "Spiker1", type = "Spiker", x = 2370, y = 448, width = 125, height = 320, properties = {} }, { name = "Spiker2", type = "Spiker", x = 2562, y = 448, width = 125, height = 320, properties = {} }, { name = "Blocks that fail once gotten on", type = "", x = 3584, y = 1408, width = 2112, height = 64, properties = {} }, { name = "In-escapable fire", type = "", x = 3584, y = 1536, width = 2112, height = 192, properties = {} }, { name = "", type = "", x = 5696, y = 1344, width = 448, height = 192, properties = {} }, { name = "Switch3", type = "Switch", x = 6080, y = 1216, width = 64, height = 64, properties = {} }, { name = "", type = "", x = 1472, y = 128, width = 64, height = 128, properties = {} }, { name = "", type = "", x = 1728, y = 128, width = 64, height = 128, properties = {} }, { name = "", type = "", x = 1984, y = 128, width = 64, height = 128, properties = {} }, { name = "", type = "", x = 3328, y = 512, width = 128, height = 192, properties = {} }, { name = "", type = "", x = 2880, y = 384, width = 192, height = 128, properties = {} }, { name = "", type = "", x = 3584, y = 896, width = 320, height = 64, properties = {} }, { name = "", type = "Box", x = 2287, y = 994, width = 64, height = 64, properties = {} } } }, { type = "objectgroup", name = "Physics", visible = false, opacity = 1, properties = { ["type"] = "physicslayer" }, objects = { { name = "", type = "", x = 0, y = 1536, width = 448, height = 448, properties = {} }, { name = "", type = "", x = 448, y = 1728, width = 512, height = 192, properties = {} }, { name = "", type = "", x = 960, y = 1536, width = 320, height = 384, properties = {} }, { name = "", type = "", x = 1600, y = 1600, width = 1792, height = 320, properties = {} }, { name = "", type = "", x = 1856, y = 1472, width = 448, height = 64, properties = {} }, { name = "", type = "", x = 2048, y = 1408, width = 256, height = 64, properties = {} }, { name = "", type = "", x = 2112, y = 1344, width = 192, height = 64, properties = {} }, { name = "", type = "", x = 2240, y = 1280, width = 64, height = 64, properties = {} }, { name = "", type = "", x = 0, y = 960, width = 1216, height = 192, properties = {} }, { name = "", type = "", x = 0, y = 1216, width = 64, height = 320, properties = {} }, { name = "", type = "", x = 1280, y = 1536, width = 128, height = 64, properties = {} }, { name = "", type = "", x = 1472, y = 1536, width = 1920, height = 64, properties = {} }, { name = "", type = "", x = 960, y = 1536, width = 0, height = 0, polygon = { { x = 0, y = 0 },
            { x = 0, y = 64 },
            { x = -64, y = 64 }
          },
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 448,
          y = 1536,
          width = 0,
          height = 0,
          polygon = {
            { x = 0, y = 0 },
            { x = 64, y = 64 },
            { x = 0, y = 64 }
          },
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1216,
          y = 960,
          width = 0,
          height = 0,
          polygon = {
            { x = 0, y = 0 },
            { x = 64, y = 64 },
            { x = 64, y = 128 },
            { x = 0, y = 192 }
          },
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1600,
          y = 960,
          width = 384,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 448,
          y = 1600,
          width = 64,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 896,
          y = 1600,
          width = 64,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2304,
          y = 1152,
          width = 512,
          height = 384,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3392,
          y = 1536,
          width = 192,
          height = 384,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3456,
          y = 1408,
          width = 128,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3584,
          y = 1728,
          width = 2560,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 5696,
          y = 1536,
          width = 448,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 6144,
          y = 1280,
          width = 256,
          height = 640,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 6220,
          y = 1918,
          width = 86,
          height = 10,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 6144,
          y = 0,
          width = 256,
          height = 1216,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 6208,
          y = 1216,
          width = 192,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 0,
          y = 0,
          width = 448,
          height = 704,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 0,
          y = 704,
          width = 192,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 0,
          y = 832,
          width = 192,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 0,
          y = 768,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 448,
          y = 384,
          width = 448,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 896,
          y = 384,
          width = 192,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 448,
          y = 0,
          width = 2880,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1024,
          y = 640,
          width = 1344,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1600,
          y = 704,
          width = 768,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1600,
          y = 768,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1600,
          y = 832,
          width = 64,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1600,
          y = 896,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2176,
          y = 512,
          width = 192,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2304,
          y = 384,
          width = 64,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2368,
          y = 384,
          width = 512,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2496,
          y = 448,
          width = 64,
          height = 320,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2816,
          y = 320,
          width = 384,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2688,
          y = 448,
          width = 192,
          height = 320,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2880,
          y = 512,
          width = 320,
          height = 256,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3072,
          y = 768,
          width = 128,
          height = 384,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3200,
          y = 960,
          width = 384,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3456,
          y = 1152,
          width = 2240,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 5568,
          y = 960,
          width = 128,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3840,
          y = 768,
          width = 576,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3968,
          y = 704,
          width = 448,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4160,
          y = 640,
          width = 256,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4224,
          y = 512,
          width = 192,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4288,
          y = 448,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3328,
          y = 0,
          width = 768,
          height = 448,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3328,
          y = 448,
          width = 704,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 3456,
          y = 512,
          width = 384,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4096,
          y = 0,
          width = 832,
          height = 256,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4928,
          y = 0,
          width = 768,
          height = 384,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 5696,
          y = 0,
          width = 448,
          height = 320,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 5568,
          y = 384,
          width = 128,
          height = 320,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4544,
          y = 448,
          width = 192,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4736,
          y = 512,
          width = 64,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4800,
          y = 576,
          width = 320,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 5120,
          y = 576,
          width = 448,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 4416,
          y = 832,
          width = 704,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1280,
          y = 448,
          width = 128,
          height = 192,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1152,
          y = 576,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 1984,
          y = 1024,
          width = 128,
          height = 128,
          properties = {}
        },
        {
          name = "",
          type = "",
          x = 2112,
          y = 1024,
          width = 64,
          height = 64,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Triggers",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "LaunchHarpoon",
          type = "Trigger",
          x = 1280,
          y = 1088,
          width = 320,
          height = 64,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Sockets",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "SS2",
          type = "SquareSocket",
          x = 1600,
          y = 1280,
          width = 64,
          height = 64,
          properties = {}
        },
        {
          name = "SS1",
          type = "SquareSocket",
          x = 1408,
          y = 1536,
          width = 64,
          height = 64,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Buttons",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "switch_1",
          type = "Switch",
          x = 128,
          y = 768,
          width = 64,
          height = 64,
          properties = {}
        },
        {
          name = "switch_2",
          type = "Switch",
          x = 1664,
          y = 832,
          width = 64,
          height = 64,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Traps",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {}
    },
    {
      type = "objectgroup",
      name = "Areas",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "area_4",
          type = "Area",
          x = 896,
          y = 704,
          width = 128,
          height = 64,
          properties = {}
        },
        {
          name = "area_3",
          type = "Area",
          x = 768,
          y = 768,
          width = 256,
          height = 64,
          properties = {}
        },
        {
          name = "area_2",
          type = "Area",
          x = 640,
          y = 832,
          width = 384,
          height = 64,
          properties = {}
        },
        {
          name = "area_a1",
          type = "Area",
          x = 512,
          y = 896,
          width = 512,
          height = 64,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Elements",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "fe_f1",
          type = "FireElement",
          x = 2816,
          y = 1152,
          width = 640,
          height = 384,
          properties = {}
        }
      }
    },
    {
      type = "objectgroup",
      name = "Data",
      visible = false,
      opacity = 1,
      properties = {},
      objects = {
        {
          name = "Scripts",
          type = "ScriptLoader",
          x = 0,
          y = 0,
          width = 256,
          height = 192,
          properties = {
            ["SS1Script"] = "Assets/Scripts/Sockets/SS1Script.lua",
            ["SS2Script"] = "Assets/Scripts/Sockets/SS2Script.lua"
          }
        }
      }
    }
  }
}
