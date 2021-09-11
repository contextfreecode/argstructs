{-# LANGUAGE NamedFieldPuns #-}

import Data.List
import Text.Printf

data ListingArgs a = ListingArgs {items :: [a], sep :: String, ends :: String}

listingArgsDefaults :: ListingArgs a
listingArgsDefaults = ListingArgs {items = [], sep = ", ", ends = "[]"}

-- listing :: Show a => ListingArgs a -> String
-- listing ListingArgs {items, sep, ends} =
-- listing :: Show a => ([a], String, String) -> String
-- listing (items, sep, ends) =
listing :: Show a => [a] -> String -> String -> String
listing items sep ends =
  printf "%s%s%s" begin (intercalate sep $ map show items) end
  where
    begin = take 1 ends
    end = take 1 $ drop 1 ends

main =
  putStrLn text
  where
    text = listing [1, 2, 3] ";" "[]"
    -- text = listing ([1, 2, 3], " ", "()")
    -- text = listing ListingArgs {items=[1, 2, 3], sep=" : ", ends=""}
    -- text = listing listingArgsDefaults {items=[1, 2, 3]}
