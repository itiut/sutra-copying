open Sys
open Arg
open List
open Printf

let linenum = ref 1
let display_linenum = ref false
let filenames = ref []
let spec = [("-n", Set display_linenum, "Display line number")]

let do_cat filename =
  (* if !file_exists filename then printf "Error: %s is not found\n"; *)
  let file = open_in filename in
  try while true do print_endline (input_line file) done with
    | End_of_file -> ()

let _ = parse spec (fun s -> filenames := s :: !filenames) "Usage: cat [-n] filename ...";

  (* if !display_linenum then printf "-n was turned on\n"; *)
  (* iter (fun s -> printf "specified filename is: %s\n" s) (rev !filenames) *)
  iter (fun s -> do_cat s) (rev !filenames)
