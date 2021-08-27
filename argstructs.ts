type ListInts = [items: number[], sep: string, ends: string];
// type ListInts = {items: number[], sep: string, ends: string};

// function listInts({items, sep, ends}: ListInts): string {
// function listInts(...[items, sep = ", ", ends = "[]"]: ListInts): string {
// function listInts(...[items, sep, ends]: ListInts): string {
// function listInts(items: number[], sep = ", ", ends = "[]"): string {
function listInts(items: number[], sep: string, ends: string): string {
  const begin = ends.slice(0, 1);
  const end = ends.slice(1, 2);
  const joined = items.join(sep);
  return `${begin}${joined}${end}`;
}

function main() {
  const text = listInts([1, 2, 3], ", ", "[]");
  // const text = listInts([1, 2, 3]);
  // const text = listInts(...[[1, 2, 3], ", ", "[]"] as ListInts);
  // const text = listInts({items: [1, 2, 3], sep: ", ", ends: "[]"});
  console.log(text);
}

main();
