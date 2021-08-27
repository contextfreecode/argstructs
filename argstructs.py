import dataclasses as dc
import typing as tp


# @dc.dataclass
# class ListInts:
#     items: list[int]
#     sep: str = ", "
#     ends: str = "[]"


# class ListInts(tp.TypedDict):
#     items: list[int]
#     sep: str
#     ends: str


class ListInts(tp.NamedTuple):
    items: list[int]
    sep: str
    ends: str


# ListInts = tuple[list[int], str, str]


# def list_ints(sep=", ", *items: int, ends: str) -> str:
# def list_ints(*args: ListInts) -> str:
def list_ints(items: list[int], sep: str, ends: str) -> str:
    # items, sep, ends = args
    begin = ends[:1]
    end = ends[1:2]
    joined = sep.join(str(i) for i in items)
    return f"{begin}{joined}{end}"


def main():
    text = list_ints([1, 2, 3], ", ", "[]")
    # text = list_ints ([1, 2, 3], ", ", "[]")
    # text = list_ints(*([1, 2, 3], ", ", "[]"))
    # text = list_ints(*tp.cast(ListInts, ([1, 2, 3], ", ", "[]")))
    # text = list_ints(*ListInts([1, 2, 3], ", ", "[]"))
    # text = list_ints(items=[1, 2, 3], sep=", ", ends="[]")
    # text = list_ints(*ListInts(items=[1, 2, 3], sep=", ", ends="[]"))
    # text = list_ints(**{"items": [1, 2, 3], "sep": ", ", "ends": "[]"})
    # text = list_ints(**dict(items=[1, 2, 3], sep=", ", ends="[]"))
    # text = list_ints(**ListInts(items=[1, 2, 3], sep=", ", ends="[]")._asdict())
    # text = list_ints(**ListInts(items=[1, 2, 3], sep=", ", ends="[]"))
    # text = list_ints(**ListInts(items=[1, 2, 3], sep=", ", ends="[]").__dict__)
    print(text)


main()
