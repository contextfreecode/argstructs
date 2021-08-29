{-# LANGUAGE FlexibleInstances, NamedFieldPuns, OverlappingInstances #-}

import Data.List
import Text.Printf

class Join r where
    join :: Show a => String -> a -> r

instance Join String where
    join sep item = show item

-- instance (Show a) => Join (a -> r) where
--     join sep item = join . ((show item) ++ sep ++)

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
        end = take 1 $ tail ends

main = putStrLn $
    listing [1, 2, 3] ";" "()"
    -- listing ([1, 2, 3], ", ", "[]")
    -- listing ListingArgs {items=[1, 2, 3], sep=", ", ends="[]"}
    -- listing listingArgsDefaults {items=[1, 2, 3]}
