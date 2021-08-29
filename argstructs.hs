{-# LANGUAGE FlexibleInstances, NamedFieldPuns, UndecidableInstances #-}

import Data.List
import Text.Printf

class Show' a where
    show' :: a -> String

instance Show a => Show' a where
    show' = show

instance {-# OVERLAPS #-} Show' String where
    show' = id

class Join r where
    join :: (Show' a) => String -> a -> r

instance Join String where
    join sep = show'

instance (Show' a, Join r) => Join (a -> r) where
    join sep acc x = join sep (show' acc ++ sep ++ show' x)

data ListingArgs a = ListingArgs {items :: [a], sep :: String, ends :: String}

listingArgsDefaults :: ListingArgs a
listingArgsDefaults = ListingArgs {items=[], sep=", ", ends="[]"}

-- listing :: Show a => ListingArgs a -> String
-- listing ListingArgs {items, sep, ends} =
-- listing :: Show a => ([a], String, String) -> String
-- listing (items, sep, ends) =
-- listing :: Show a => [a] -> String -> String -> String
listing items sep ends =
    printf "%s%s%s" begin (intercalate sep $ map show items) end
    where
        begin = take 1 ends
        end = drop 1 ends

main = putStrLn $
    -- listing [1, 2, 3] ";" "[]"
    -- listing ([1, 2, 3], " ", "()")
    -- listing ListingArgs {items=[1, 2, 3], sep=" : ", ends=""}
    -- listing listingArgsDefaults {items=[1, 2, 3]}
    join ";" (1 :: Int) (2 :: Int) (3 :: Int) "last"
