module Lib
  ( MyCricle (..),
    Point (..),
    someFunc,
    surface,
  )
where

someFunc :: IO ()
someFunc = print (surface (Circle (Point 1 2) 3))

--- >>> [ (x,y,z) | x <- [1..21], y <- [1..21], z <- [1..21], x<=y, x**2 + y**2 == z**2]
-- [(3.0,4.0,5.0),(5.0,12.0,13.0),(6.0,8.0,10.0),(8.0,15.0,17.0),(9.0,12.0,15.0),(12.0,16.0,20.0)]
data Point = Point {x :: !Float, y :: !Float} deriving (Show)

--- >>> abs $ 3 - 4 
-- 1
data MyCricle = Circle {point :: !Point, len :: !Float} | Rectangle {left_bellow :: !Point, right_up :: !Point} deriving (Show)

--- >>>  (surface (Circle (Point 1 2 ) 3 ))
-- 28.26
surface :: MyCricle -> Float
surface (Circle _ a) = pi * a ^ 2
  where
    pi = 3.14
surface (Rectangle (Point x1 y1) (Point x2 y2)) = abs (x2 - x1) * abs (y2 - y1)
