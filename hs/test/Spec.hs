import Lib (MyCricle (..), Point (..), surface)

main :: IO ()
main = print (surface (Circle (Point 1.0 2.0) 3))
