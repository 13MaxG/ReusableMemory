#pragma once
#include "Reusable.hpp"
#include <Eigen/Dense>

// Private
#define _ReusableMatrixTypeName ReusablePool<std::pair<size_t, size_t>, Eigen::MatrixXd>

template<>
Eigen::MatrixXd* _ReusableMatrixTypeName::construct(const std::pair<size_t, size_t>& sizes) {
    return new Eigen::MatrixXd(sizes.first, sizes.second);
}

// Public
#define ReusableMatrix _ReusableMatrixTypeName::instance()