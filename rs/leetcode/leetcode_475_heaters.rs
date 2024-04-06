// Winter is coming! During the contest
// your first job is to design a standard heater with a fixed warm radius to
// warm all the houses.
//
// Every house can be warmed, as long as the house is within the heater's warm
// radius range.
//
// Given the positions of houses and heaters on a horizontal line,
// return the minimum radius standard of heaters so that those heaters could
// cover all houses.
//
// Notice that all the heaters follow your radius standard, and the warm radius
// will the same.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_radius(houses: &[i32], heaters: &[i32]) -> i32 {
        houses
            .iter()
            .map(
                |h| {
                    heaters
                        .iter()
                        .map(|ht| (h - ht).abs())
                        .min() // the smallest absolute difference between current
                        // house and each heater will be the closest heater to
                        // that house
                        .unwrap_or(i32::MIN)
                }, // if heaters is empty return the smallest possible value
            )
            .max() // to cover all the houses the radius must be the largest minimal
            // distance between any house and its closest heater
            .unwrap_or(i32::MAX) // if houses is empty return the largest
                                 // possible value    }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let houses = vec![1, 2, 3];
        let heaters = vec![2];
        let ret = Solution::find_radius(&houses, &heaters);
        assert_eq!(ret, 1);
        // The only heater was placed in the position 2, and if we use the
        // radius 1 standard, then all the houses can be warmed.
    }

    #[test]
    fn case2_test() {
        let houses = vec![1, 2, 3, 4];
        let heaters = vec![1, 4];
        let ret = Solution::find_radius(&houses, &heaters);
        assert_eq!(ret, 1);
        // The two heater was placed in the position 1 and 4. We need to use
        // radius 1 standard, then all the houses can be warmed.
    }
    #[test]
    fn case3_test() {
        let houses = vec![1, 5];
        let heaters = vec![2];
        let ret = Solution::find_radius(&houses, &heaters);
        assert_eq!(ret, 3);
    }
}
