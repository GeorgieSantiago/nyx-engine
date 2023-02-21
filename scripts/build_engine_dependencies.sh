bazel query "deps(//:nyx_engine)" --noimplicit_deps --output graph >> engine_graph.ini && dot -Tpng < engine_graph.ini > engine_graph.png
