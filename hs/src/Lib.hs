module Lib
  ( MyCricle (..),
    Point (..),
    someFunc,
    surface,
  )
where

someFunc :: IO ()
someFunc = print (surface (Circle (Point 1 2) 3))

data Point = Point {x :: !Float, y :: !Float} deriving (Show)

data MyCricle = Circle {point :: !Point, len :: !Float} | Rectangle {left_bellow :: !Point, right_up :: !Point} deriving (Show)

surface :: MyCricle -> Float
surface (Circle _ a) = pi * a ^ 2
  where
    pi = 3.14
surface (Rectangle (Point x1 y1) (Point x2 y2)) = abs (x2 - x1) * abs (y2 - y1)
