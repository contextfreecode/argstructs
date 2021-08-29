{-# LANGUAGE FlexibleInstances, NamedFieldPuns #-}

import Data.List
import Text.Printf

class Join r where
    -- join :: Show a => a -> r
    join :: String -> r

instance Join String where
    join = id

instance Join r => Join (String -> r) where
    -- join sep acc x = join sep (acc ++ sep ++ x)
    join acc x = join (acc ++ " " ++ x)

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
    join ";" "a" "b"
    -- listing [1, 2, 3] ";" "[]"
    -- listing ([1, 2, 3], " ", "()")
    -- listing ListingArgs {items=[1, 2, 3], sep=" : ", ends=""}
    -- listing listingArgsDefaults {items=[1, 2, 3]}
