// class ListingArgs {
//   constructor(
//     items: unknown[],
//     sep?: string,
//     ends?: string,
//   ) {
//     this.items = items;
//     if (sep != null) this.sep = sep;
//     if (ends != null) this.ends = ends;
//   }
//   items: unknown[];
//   sep = ", ";
//   ends = "[]";
// }
// const listIntDefaults = Object.freeze({sep: ", ", ends: "[]"});
// type ListingArgs = {items: unknown[], sep: string, ends: string};
// type NumberArray = number[];  // or Array<number>
// type ListingArgs = [...items: unknown[], sep: string, ends: string];
type ListingArgs = [sep: string, ends: string, ...items: unknown[]];
// type ListingArgs = [items: unknown[], sep: string, ends: string];

// function listing({items, sep, ends}: ListingArgs): string {
// function listing(...[items, sep = ", ", ends = "[]"]: ListingArgs): string {
// function listing(...[items, sep, ends]: ListingArgs): string {
// function listing(sep = ", ", ends = "[]", items: unknown[]): string {
// function listing(items: unknown[], sep = ", ", ends = "[]"): string {
// function listing(...items: unknown[], sep: string, ends = "[]"): string {
// function listing(sep: string, ends = "[]", ...items: unknown[]): string {
function listing(items: unknown[], sep: string, ends: string): string {
  const begin = ends.slice(0, 1);
  const end = ends.slice(1, 2);
  const joined = items.join(sep);
  return `${begin}${joined}${end}`;
}

function main() {
  const text = listing([1, 2, 3], ", ", "[]");
  // const text = listing(", ", "[]", 1, 2, 3);
  // const text = listing(...[", ", "[]", 1, 2, 3] as ListingArgs);
  // const text = listing(", ");
  // const text = listing();
  // const text = listing(new ListingArgs([1, 2, 3]));
  // const text = listing([1, 2, 3]);
  // const text = listing(...[[1, 2, 3], ", ", "[]"] as ListingArgs);
  // const text = listing({items: [1, 2, 3], sep: ", ", ends: "[]"});
  // const text = listing({...listIntDefaults, items: [1, 2, 3]});
  console.log(text);
}

main();
