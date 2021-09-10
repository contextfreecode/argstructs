import dataclasses as dc
import typing as tp


# @dc.dataclass
# class ListingArgs:
#     items: list
#     sep: str = ", "
#     ends: str = "[]"


# class ListingArgs(tp.TypedDict):
#     items: list
#     sep: str
#     ends: str


# class ListingArgs(tp.NamedTuple):
#     items: list
#     sep: str = ", "
#     ends: str = "[]"


ListingArgs = tuple[list, str, str]


# def listing(*items, sep=", ", ends: str = "[]") -> str:
# def listing(sep, *items, ends: str = "[]") -> str:
# def listing(**args) -> str:
# def listing(*args) -> str:
def listing(items: list, sep: str = ", ", ends: str = "[]") -> str:
    # items, sep, ends = tp.cast(ListingArgs, args)
    # {items, sep, ends} = tp.cast(ListingArgs, args)
    # items = args["items"]; sep = args["sep"]; ends = args["ends"]
    # match tp.cast(ListingArgs, args):
    #     case {"items": items, "sep": sep, "ends": ends}: pass
    #     case _: assert False
    begin = ends[:1]
    end = ends[1:2]
    joined = sep.join(str(i) for i in items)
    return f"{begin}{joined}{end}"


def main():
    text = listing([1, 2, 3], " ", "[]")
    # text = listing ([1, 2, "three"], " ", "[]")
    # text = listing(*([1, 2, 3], "; ", "[]"))
    # text = listing(*tp.cast(ListingArgs, ([1, 2, 3], " ", "()")))
    # text = listing(*ListingArgs([1, 2, 3], "; ", "()"))
    # text = listing(items=[1, 2, 3], sep=", ", ends="()")
    # text = listing(*ListingArgs(items=[1, 2, 3], sep="/", ends="()"))
    # text = listing(**{"items": [1, 2, 3], "sep": " ", "ends": "<>"})
    # text = listing(**dict(items=[1, 2, 3], sep=", ", ends="<>"))
    # text = listing(**ListingArgs(items=[1, 2, 3], sep="; ", ends="<>")._asdict())
    # text = listing(**ListingArgs(items=[1, 2, 3], sep="/", ends="<>"))
    # text = listing(**ListingArgs(items=[1, 2, 3], sep=", ", ends="").__dict__)
    # text = listing(" ", 1, 2, 3, ends="")
    # text = listing(sep=":", 1, 2, 3, ends="")
    # text = listing(1, 2, 3, sep="/", ends="")
    # text = listing(1, 2, 3)
    print(text)


main()
