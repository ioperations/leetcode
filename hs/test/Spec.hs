import Lib (MyCricle (..), Point (..), surface)
import qualified Data.Map as Map

main :: IO ()
main = print (surface (Circle (Point 1.0 2.0) 3))


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
-- Left "Locker 100 is already taken!"
-- Right "JAH3I"
-- Left "Locker number 102 doesn't exist!"
-- Right "IQSA9"
-- Left "Locker number 104 doesn't exist!"

