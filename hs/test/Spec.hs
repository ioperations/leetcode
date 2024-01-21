import Lib (MyCricle (..), Point (..), surface)
import qualified Data.Map as Map

t :: Int -> Int 
t q = q +1 

getnn:: (String, Int) -> String
getnn (a, b ) = a 


main :: IO ()
main = do
    let fmaps =   (fmap (+3) (Just 1)) 
    let ap = (\x -> x +1 )  <$> [4]
    case fmaps of 
        Just q -> putStrLn $ "v: " ++ show q 
        Nothing -> putStrLn $ "nothing " 
    let moland' = ( getnn $ ("hello", 2) >>= (\x -> (" world",  x + 3 )))
    putStrLn $ show fmaps ++ " "  ++ " applicative " ++ show ap ++ moland'
    putStrLn $ show $ surface (Circle  (Point 1 2) 2)


data LockerState = Taken | Free deriving (Show, Eq)

type Code = String

type LockerMap = Map.Map Int (LockerState, Code)

lockerLookup :: Int -> LockerMap -> Either String Code
lockerLookup lockerNumber map =
    case Map.lookup lockerNumber map of
        Nothing -> Left $ "Locker number " ++ show lockerNumber ++ " doesn't exist!"
        Just (state, code) -> if state /= Taken
                                then Right code
                                else Left $ "Locker " ++ show lockerNumber ++ " is already taken!"

lockers :: LockerMap
lockers = Map.fromList
    [(100,(Taken,"ZD39I"))
    ,(101,(Free,"JAH3I"))
    ,(103,(Free,"IQSA9"))
    ,(105,(Free,"QOTSA"))
    ,(109,(Taken,"893JJ"))
    ,(110,(Taken,"99292"))
    ]



--- >>> lockerLookup 100 lockers
--- >>> lockerLookup 101 lockers
--- >>> lockerLookup 102 lockers
--- >>> lockerLookup 103 lockers
--- >>> lockerLookup 104 lockers


