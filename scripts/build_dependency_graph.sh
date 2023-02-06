bazel query "deps(//:all)" --noimplicit_deps --output graph >> graph.in && dot -Tpng < graph.in > graph.png
