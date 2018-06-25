//
// Created by Ted Klein Bergman on 3/6/18.
//

#ifndef OPENGLPROJECT_OBJ_LOADER_H
#define OPENGLPROJECT_OBJ_LOADER_H

const char* const OBJ_POSITION_ATTRIBUTE = "v";
const char* const OBJ_TEXTURE_COORDINATE_ATTRIBUTE = "vt";
const char* const OBJ_NORMAL_ATTRIBUTE = "vn";
const char OBJ_FACE_ATTRIBUTE = 'f';
const char OBJ_VERTEX_DATA_DELIMITER = ' ';
const char OBJ_FACE_DATA_DELIMITER = '/';

#include <vector>
#include <glad/glad.h>

#include "glm/glm.hpp"


struct OBJData
{
    std::vector<GLfloat> data;
    std::vector<unsigned int> indices;
};

OBJData load_obj_file(const char* path, bool normalize = false);





//
//#include <iostream>     // std::ios, std::istream, std::cout
//#include <fstream>      // std::filebuf
//#include <limits>       // numeric_limits
//#include <sstream>
//#include <string>
//#include <vector>
//#include <iterator>
//
//
//struct VertexData
//{
//    std::vector<ValueType> positions;
//    std::vector<ValueType> texture_coordinates;
//    std::vector<ValueType> normals;
//    std::vector<IndexType> indices;
//};
//
//struct Face
//{
//    std::array<int, VerticesPerFace> vertices;
//};
//
//struct FaceData
//{
//    std::vector<Face> faces;
//};
//
//struct VertexIndex
//{
//    int position;
//    int texture_coordinate;
//    int normal;
//};
//
//
//std::vector<std::string> split(const std::string& string, char delimiter)
//{
//    std::vector<std::string> result;
//    std::stringstream ss(string);
//    std::string item;
//    while (std::getline(ss, item, delimiter))
//        result.push_back(item);
//    return result;
//}
//
//template <typename T>
//T convert(const std::string& string);
//
//template <>
//float convert(const std::string& string)
//{
//    return std::stof(string);
//}
//
//template <>
//double convert(const std::string& string)
//{
//    return std::stof(string);
//}
//
//std::vector<float> read_values(std::istream& stream)
//{
//    std::string line;
//    std::getline(stream, line);
//    std::vector<float> values;
//    for (std::string& item : split(line, OBJ_VERTEX_DATA_DELIMITER))
//    {
//        float value = convert<float>(item);
//        values.push_back(value);
//    }
//    return values;
//}
//
//template <typename T>
//void extend_vector(std::vector<T>& extendable, const std::vector<T>& values)
//{
//    extendable.insert(extendable.end(), values.begin(), values.end());
//}
//
//void read_vertex_data(std::istream& stream, VertexData<T, I>& data)
//{
//    std::string attribute;
//    std::getline(stream, attribute, OBJ_VERTEX_DATA_DELIMITER);
//    std::vector<float> values = read_values(stream);
//
//    if (attribute == OBJ_POSITION_ATTRIBUTE)
//        extend_vector<float>(data.positions, values);
//    else if (attribute == OBJ_TEXTURE_COORDINATE_ATTRIBUTE)
//        extend_vector<float>(data.texture_coordinates, values);
//    else if (attribute == OBJ_NORMAL_ATTRIBUTE)
//        extend_vector<float>(data.normals, values);
//    else
//        throw std::runtime_error("Unknown attribute!");
//}
//
//
//void read_face_data(std::istream& stream, FaceData<3>& data)
//{
//    stream.ignore(OBJ_FACE_ATTRIBUTE);
//
//    std::string line;
//    std::getline(stream, line);
//
//    for (std::string& vertex : split(line, OBJ_VERTEX_DATA_DELIMITER))
//    {
//        Face<3> face;
//        int i = 0;
//        for (std::string& value : split(vertex, OBJ_FACE_DATA_DELIMITER))
//            face[i++] = convert<float>(value);
//
//        data.faces.push_back(face);
//    }
//
//}
//
//VertexData<T, I> read(std::istream& stream)
//{
//    constexpr int until_end = std::numeric_limits<int>::max();
//    VertexData<T, I> data;
//
//    while (stream)
//    {
//        if (stream.peek() == 'v')
//            read_vertex_data<T, I>(stream, data);
//        else if (stream.peek() == 'f')
//            read_face_data<3>(stream, data);
//        else
//            stream.ignore(until_end, '\n');  // Skip line until end of line or until EOF.
//    }
//    return data;
//}
//
//template <typename T, typename I>
//OBJData load_obj_file2(const std::string& path)
//{
//    std::filebuf file_buffer;
//
//    bool opened = (bool)file_buffer.open(path, std::ios::in);
//    if (opened)
//    {
//        std::istream input_stream(&file_buffer);
//        read<T, I>(input_stream);
//        file_buffer.close();
//    }
//}
//
//

#endif //OPENGLPROJECT_OBJ_LOADER_H
