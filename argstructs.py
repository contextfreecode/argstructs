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


# def listing(kwargs: ListingArgs) -> str:
# def listing((items, sep, ends): ListingArgs) -> str:
# def listing(args: ListingArgs) -> str:
def listing(items: list, sep: str = ", ", ends: str = "[]") -> str:
    # items, sep, ends = args
    # {items, sep, ends} = kwargs
    # items = kwargs["items"]; sep = kwargs["sep"]; ends = kwargs["ends"]
    begin = ends[:1]
    end = ends[1:2]
    joined = sep.join(str(i) for i in items)
    return f"{begin}{joined}{end}"


def main():
    text = listing([1, 2, 3], " ", "()")
    # text = listing ([1, 2, 3], " : ", "()")
    # text = listing(*([1, 2, 3], "; ", "[]"))
    # text = listing(([1, 2, 3], " ", "()"))
    # text = listing(*ListingArgs([1, 2, 3], "; ", "()"))
    # text = listing(items=[1, 2, 3], sep=" ", ends="()")
    # text = listing(**{"items": [1, 2, 3], "sep": " ", "ends": "<>"})
    # text = listing({"items": [1, 2, 3], "sep": " ", "ends": "<>"})
    # text = listing(*ListingArgs(items=[1, 2, 3], sep="/", ends="()"))
    # text = listing(**dict(items=[1, 2, 3], sep=", ", ends="<>"))
    # text = listing(**ListingArgs(items=[1, 2, 3], sep="; ", ends="<>")._asdict())
    # text = listing(**ListingArgs(items=[1, 2, 3], sep="/", ends="<>"))
    # text = listing(**ListingArgs(items=[1, 2, 3], sep=", ", ends="").__dict__)
    print(text)


main()
