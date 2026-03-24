import sys
import os

def parse_blocks(filepath: str) -> list[list[str]]:
    with open(filepath, "r") as f:
        lines: list[str] = [line.rstrip('\n') for line in f.readlines()]
    blocks: list[list[str]] = []
    current_block: list[str] = []
    for line in lines:
        if line.strip() == "":
            if current_block:
                blocks.append(current_block)
                current_block = []
        else:
            current_block.append(line)
    if current_block:
        blocks.append(current_block)
    return blocks

def parse_blocks_lower(filepath: str) -> list[list[str]]:
    with open(filepath, "r") as f:
        lines: list[str] = [line.rstrip('\n') for line in f.readlines()]
    blocks: list[list[str]] = []
    current_block: list[str] = []
    for line in lines:
        s = line.strip()
        if len(s) == 1 and s.islower() and s.isalpha():
            if current_block:
                blocks.append(current_block)
            current_block = []
        else:
            current_block.append(line)
    if current_block:
        blocks.append(current_block)
    return blocks

def convert(font_name: str, output_file: str, file_upper: str, file_lower: str) -> None:
    blocks_upper: list[list[str]] = parse_blocks(file_upper)
    blocks_lower: list[list[str]] = parse_blocks_lower(file_lower)
    
    letters_upper: list[list[str]] = [blocks_upper[i] for i in range(2, min(28, len(blocks_upper)))]
    # Lowercase blocks are now cleanly separated by the label.
    # The label line is consumed and not appended to current_block.
    letters_lower: list[list[str]] = [blocks_lower[i] for i in range(min(26, len(blocks_lower)))]
    
    # Strip any trailing blank lines from all character blocks
    for b in letters_upper + letters_lower:
        while len(b) > 0 and b[-1].strip() == "":
            b.pop()
            
    height: int = max(max([len(b) for b in letters_upper] + [0]), max([len(b) for b in letters_lower] + [0]))
    
    out: list[str] = []
    out.append('#include "../include/tuil_fonts.h"\n')
    
    # Generate upper
    out.append(f'static const char* char_ptrs_upper_{font_name}[26][{height}] = {{')
    for i, letter_lines in enumerate(letters_upper):
        char_name: str = chr(ord('A') + i)
        out.append(f"    // {char_name}")
        out.append("    {")
        max_w = max([len(l.rstrip()) for l in letter_lines] + [0])
        for j in range(height):
            line: str = letter_lines[j] if j < len(letter_lines) else ""
            line = line.rstrip().ljust(max_w)
            escaped: str = line.replace('\\', '\\\\').replace('"', '\\"')
            out.append(f'        "{escaped}",')
        out.append("    },")
    out.append("};\n")
    
    # Generate lower
    out.append(f'static const char* char_ptrs_lower_{font_name}[26][{height}] = {{')
    for i, letter_lines in enumerate(letters_lower):
        char_name: str = chr(ord('a') + i)
        out.append(f"    // {char_name}")
        out.append("    {")
        max_w = max([len(l.rstrip()) for l in letter_lines] + [0])
        for j in range(height):
            line: str = letter_lines[j] if j < len(letter_lines) else ""
            line = line.rstrip().ljust(max_w)
            escaped: str = line.replace('\\', '\\\\').replace('"', '\\"')
            out.append(f'        "{escaped}",')
        out.append("    },")
    out.append("};\n")
    
    # Create object
    out.append(f"const tuil_font_t tuil_font_{font_name} = {{")
    out.append(f'    "{font_name}",')
    out.append(f"    {height},")
    out.append('    {')
    for i in range(26):
        out.append(f"        ['{chr(ord('A') + i)}'] = (const char**)char_ptrs_upper_{font_name}[{i}],")
        out.append(f"        ['{chr(ord('a') + i)}'] = (const char**)char_ptrs_lower_{font_name}[{i}],")
    out.append("    }")
    out.append("};\n")
    
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, "w") as f:
        f.write("\n".join(out))
        
    # Auto-register into tuil_fonts.h
    header_path = os.path.join(os.path.dirname(output_file), "../../include/tuil_fonts.h")
    header_path = os.path.normpath(header_path)
    if os.path.exists(header_path):
        with open(header_path, "r") as hf:
            content = hf.read()
            
        extern_decl = f"extern const tuil_font_t tuil_font_{font_name};"
        macro_decl = f"#define FONT_{font_name.upper()} &tuil_font_{font_name}"
        
        if extern_decl not in content:
            content = content.replace("#endif", f"{extern_decl}\n{macro_decl}\n\n#endif")
            with open(header_path, "w") as hf:
                hf.write(content)

if __name__ == "__main__":
    convert(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
