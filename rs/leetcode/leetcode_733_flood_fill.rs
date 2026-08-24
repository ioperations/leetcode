// You are given an image represented by an m x n grid of integers image, where
// image[i][j] represents the pixel value of the image. You are also given three
// integers sr, sc, and color. Your task is to perform a flood fill on the image
// starting from the pixel image[sr][sc].
//
// To perform a flood fill:
//
// Begin with the starting pixel and change its color to color.
// Perform the same process for each pixel that is directly adjacent (pixels
// that share a side with the original pixel, either horizontally or vertically)
// and shares the same color as the starting pixel. Keep repeating this process
// by checking neighboring pixels of the updated pixels and modifying their
// color if it matches the original color of the starting pixel. The process
// stops when there are no more adjacent pixels of the original color to update.
// Return the modified image after performing the flood fill.
//
// m == image.length
// n == image[i].length
// 1 <= m, n <= 50
// 0 <= image[i][j], color < 216
// 0 <= sr < m
// 0 <= sc < n

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn flood_fill(
        image: Vec<Vec<i32>>,
        sr: i32,
        sc: i32,
        color: i32,
    ) -> Vec<Vec<i32>> {
        let mut ret = image;

        Self::update(&mut ret, sr, sc, color, None);

        ret
    }

    fn update(
        image: &mut Vec<Vec<i32>>,
        sr: i32,
        sc: i32,
        color: i32,
        origin_var: Option<i32>,
    ) -> bool {
        let row = image.len() as i32;
        let column = image[0].len() as i32;

        if sr >= row || sc >= column || sr < 0 || sc < 0 {
            return false;
        }
        let origin = image[sr as usize][sc as usize];
        if let Some(v) = origin_var
            && v != origin {
                return false;
            }
        if origin == color {
            return false;
        }
        image[sr as usize][sc as usize] = color;

        Self::update(image, sr - 1, sc, color, Some(origin));
        Self::update(image, sr + 1, sc, color, Some(origin));
        Self::update(image, sr, sc - 1, color, Some(origin));
        Self::update(image, sr, sc + 1, color, Some(origin));

        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let image = [[1, 1, 1], [1, 1, 0], [1, 0, 1]]
            .into_iter()
            .map(|v| Vec::from(v))
            .collect::<Vec<Vec<_>>>();
        let sr = 1;
        let sc = 1;
        let color = 2;

        // From the center of the image with position (sr, sc) = (1, 1) (i.e.,
        // the red pixel), all pixels connected by a path of the same color as
        // the starting pixel (i.e., the blue pixels) are colored with the new
        // color.
        //
        // Note the bottom corner is not colored 2, because it is not
        // horizontally or vertically connected to the starting pixel.

        let output = [[2, 2, 2], [2, 2, 0], [2, 0, 1]]
            .into_iter()
            .map(|v| Vec::from(v))
            .collect::<Vec<Vec<_>>>();

        let ret = Solution::flood_fill(image, sr, sc, color);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let image = [[0, 0, 0], [0, 0, 0]]
            .into_iter()
            .map(|v| Vec::from(v))
            .collect::<Vec<Vec<_>>>();
        let sr = 0;
        let sc = 0;
        let color = 0;

        // The starting pixel is already colored with 0, which is the same as
        // the target color. Therefore, no changes are made to the image.

        let output = [[0, 0, 0], [0, 0, 0]]
            .into_iter()
            .map(|v| Vec::from(v))
            .collect::<Vec<Vec<_>>>();

        let ret = Solution::flood_fill(image, sr, sc, color);
        assert_eq!(output, ret);
    }
}
