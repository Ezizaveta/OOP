#include "PyramidalDecompositor.h"

std::vector<SubMat> PyramidalDecompositor::decompose(const cv::Mat& mat, const AbstractPolicy<uchar>& policy)
{
	cv::Mat new_mat = mat.clone();
	std::vector<SubMat> result;
	int current_lvl = 1;
	while (new_mat.rows > 1 && new_mat.cols > 1) {
		new_mat = compress(new_mat, policy);
		result.emplace_back(new_mat, current_lvl);
		current_lvl++;
	}
	return result;
}

cv::Mat PyramidalDecompositor::compress(const cv::Mat& mat, const AbstractPolicy<uchar>& policy)
{
		const int new_rows = mat.rows / 2;
		const int new_cols = mat.cols / 2;
		if (new_rows < 1 && new_cols < 1) {
			return mat;
		}
		cv::Mat new_mat = cv::Mat(new_rows, new_cols, mat.type());
		for (int y = 0; y < new_mat.rows; y++) {
			for (int x = 0; x < new_mat.cols; x++) 
			{
				new_mat.at<uchar>(y, x) = policy.calculate({mat.at<uchar>(y * 2, x * 2),
															mat.at<uchar>(y * 2 + 1, x * 2 + 1),
															mat.at<uchar>(y * 2 + 1, x * 2),
															mat.at<uchar>(y * 2, x * 2 + 1) });
			}
		}
		return new_mat;
}
