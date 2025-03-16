//
// Created by nvan on 08-03-2025.
//

#pragma once

/*
 * Affine transformations are geometric transformations that preserve parallel lines and ratio of distances.
 * They include: translations, rotations, scaling and shearing.
 * Affine matrices are used to represent those transformations.
 * The scaling factor is usually found along the diagonal of the matrix:
 *  - [0,0] scaling along x axis
 *  - [1,1] scaling along y axis
 *  - [2,2] scaling along z axis
 *
 * If these elements are 1 there's no scaling.
 * The scale is usually 1: this means that 1 is a common value for the elements along the diagonal.
 * If it's not 1 then it is uniform. Being uniform means that the scaled object is scaled by the same amount
 * along all the axis. This is to avoid distortions.
 *
 * So we can avoid sending everytime all the elements along the diagonal.
 * We can send a boolean value that indicates if the matrix is scaled. Let's call this boolean value "isScaled".
 * If is scaled is true we avoid to send the diagonal values.
 * Normally we use sizeof(float) * 16 bytes. sizeof(float) = 4 bytes in a 32 bit machine.
 * So this means 4 * 16 = 64 bytes
 * If isScaled is false we can avoid sending 3 floats. This means 64 - 12 + 1 = 53 bytes. The 1 is the isScaled var.
 * If isScaled is true we can still avoid sending 3 floats by using another boolean value "isUniform".
 * If isUniform we pass the value that is used to scale the matrix along the axis.
 * So we need an extra float "scaleFactor".
 * This means 64 - 12 + 2 + 4 = 58 bytes.
 * But we can also use avoid to send 32 bits for each float by using fixed point numbers.
 * For hypothesis let's say that the number of digits after the comma is 2.
 * To understand how to get a discount on some bits we have to check
 * what each position in the matrix means for the game object.
 *
 * A matrix can:
 *      - translate
 *      - scale
 *      - rotate
 *      - shear
 *
 * We could use one boolean each mode to indicate
 * what we are using the matrix for.
 * bool isTranslation
 * bool isScale
 * bool isRotating
 * bool isShearing
 *
 * For each of the type we have common values.
 * If isRotating is true the values can go from 0 to 360 degrees.
 * This means that we can represent the rotation by using log2(360) = 9 bytes
 * If isTranslation is true we can still have a movement of up to the size of the map played,
 * and just as assumption let's say the map goes from 2000 to -2000.
 * This means that we can represent the translation by using:
 * translationBytes = (2000 + 2000) / 0,1 + 1 = 40001
 *  = log2(40001) = 16 bytes
 *
 *
 *
 *
 *
 *
 * */
struct AffineMatrix {
    double matrix[4][4];
};