cmake_minimum_required(VERSION 3.21)
project(SocialApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# تفعيل AUTOMOC لـ Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# إضافة مجلدات المشروع
add_subdirectory(core)
add_subdirectory(app)
