import graphviz

# Inisialisasi graf State Diagram (Directed Graph)
dot = graphviz.Digraph(comment='State Diagram Moore', format='png')
dot.attr(rankdir='LR', size='8,5')

# Konfigurasi gaya lingkaran (node)
dot.attr('node', shape='circle', style='filled', fillcolor='lightblue', fontname='Arial')

# Menambahkan Node (Format: State / Output)
dot.node('A', 'A / 1')
dot.node('B', 'B / 0')
dot.node('C', 'C / 1')
dot.node('D', 'D / 1')

# Konfigurasi gaya panah (edge)
dot.attr('edge', fontname='Arial', fontsize='12')

# Menambahkan Edge (Transisi) beserta label Input
dot.edge('A', 'A', label=' X=0')
dot.edge('A', 'B', label=' X=1')

dot.edge('B', 'C', label=' X=0, 1')

dot.edge('C', 'C', label=' X=0')
dot.edge('C', 'D', label=' X=1')

dot.edge('D', 'C', label=' X=0, 1')

# Render dan simpan file gambar
# File akan tersimpan sebagai 'state_diagram.png' di folder yang sama
dot.render('state_diagram', view=True)
print("Diagram berhasil dibuat! Cek file 'state_diagram.png'.")