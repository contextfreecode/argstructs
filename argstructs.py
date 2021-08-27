import dataclasses as dc


@dc.dataclass
class IntListFormatting:
    sep: str = ","
    items: list[int] = dc.field(default_factory=list)
    ends: str = "[]"


def format_int_list(sep=",", *items: int, ends: str):
    pass
