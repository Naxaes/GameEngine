//
// Created by Ted Klein Bergman on 5/15/18.
//

#include "gtest/gtest.h"
#include "obj_loader.h"



TEST(read_vertex_data, returns_correct_sizes)
{
    // Arrange
    std::stringstream stream("v 1 2 3\nvt 4 5\nvn 6 7 8");
    int positions = 3;
    int texture_coordinates = 2;
    int normals = 3;

    // Act
    VertexData<float, int> data = read<float, int>(stream);

    // Assert
    ASSERT_EQ(data.positions.size(), positions);
    ASSERT_EQ(data.texture_coordinates.size(), texture_coordinates);
    ASSERT_EQ(data.normals.size(), normals);
}
