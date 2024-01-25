{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# OPTIONS_GHC -Wno-type-defaults #-}
{-# OPTIONS_GHC -Wno-name-shadowing #-}
import qualified Data.Map as Map

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

first':: (String, Maybe Int) -> String
first' (a, _ ) = a

main :: IO ()
main = do
    let fmaps = (fmap (+3) (Just 1))

    let v = show $ case (lockerLookup 100 lockers) of
                    Left s -> s
                    Right y -> y

    print (first' $
             ("fmap: " , fmap (+3) (Just 1))
                >>= (const ("fmap ", case fmaps of
                                            Just q -> Just $ show q
                                            Nothing -> Just "nothing "))
                >>= (\y -> (show y ++ ", applicative maybe " ,  (Just (+ 4) <*>  (Just  5))))
                >>= (\y -> (show y ++ ", applicative list " ,   ([(*2),(*3)] <*> [3,4,5])) )
                >>= (\y -> (show y ++ ", moland ",              Just 4 >>= (\x -> Just (x +1)) ))
                >>= (\y -> (show y, Just 0))
                >>= (const (" " ++ v, Nothing))
            )

