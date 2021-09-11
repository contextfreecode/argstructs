{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE NamedFieldPuns #-}
{-# LANGUAGE UndecidableInstances #-}

import Data.List
import Text.Printf

class Show' a where
  show' :: a -> String

instance Show a => Show' a where
  show' = show

instance {-# OVERLAPS #-} Show' String where
  show' = id

instance {-# OVERLAPS #-} Show' Item where
  show' (IntItem i) = show' i
  show' (StringItem s) = show' s

instance Show Item where
  show = show'

class Join r where
  listing' :: (Show' a) => String -> String -> a -> r

instance Join String where
  listing' sep ends x =
    begin ++ show' x ++ end
    where
      begin = take 1 ends
      end = take 1 $ drop 1 ends

instance (Show' a, Join r) => Join (a -> r) where
  listing' sep ends acc x = listing' sep ends (show' acc ++ sep ++ show' x)

listing4 sep ends (a, b, c, d) = listing' sep ends a b c d

curry6 fun (a, b, c, d, e, f) = fun a b c d e f

-- listing4' = curry6 listing'

data Item = IntItem Int | StringItem String

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
    -- text = listing [IntItem 1, IntItem 2, StringItem "three"] ";" "[]"
    -- text = listing ([1, 2, 3], " ", "()")
    -- text = listing ListingArgs {items=[1, 2, 3], sep=" : ", ends=""}
    -- text = listing listingArgsDefaults {items=[1, 2, 3]}
    -- text = listing' ";" "<>" (1 :: Int) (2 :: Int) (3 :: Int) "last"
    -- text = listing4 ";" "" (1 :: Int, 2 :: Int, 3 :: Int, "last")
    -- text = listing4'(";", "<>", 1 :: Int, 2 :: Int, 3 :: Int, "last")
