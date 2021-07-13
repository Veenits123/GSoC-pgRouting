/*PGR-GNU*****************************************************************
File: pgr_edgeColoring.cpp

Generated with Template by:
Copyright (c) 2021 pgRouting developers
Mail: project@pgrouting.org

Function's developer:
Copyright (c) 2021 Veenit Kumar
Mail: 123sveenit@gmail.com
------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 ********************************************************************PGR-GNU*/

#include "coloring/pgr_edgeColoring.hpp"
#include <boost/graph/edge_coloring.hpp>
#include <boost/graph/graph_utility.hpp>

#include <vector>
#include <utility>

#include "cpp_common/identifiers.hpp"
#include "cpp_common/pgr_assert.h"


namespace pgrouting {
namespace functions {

std::vector<pgr_vertex_color_rt>
Pgr_edgeColoring::edgeColoring() {
    std::vector<pgr_vertex_color_rt> results;

#if 0
    CHECK_FOR_INTERRUPTS();
#endif

    try {
        boost::edge_coloring(graph,  boost::get(boost::edge_bundle, graph));
    } catch (boost::exception const &ex) {
        (void)ex;
        throw;
    } catch (std::exception &e) {
        (void)e;
        throw;
    } catch (...) {
        throw;
    }

    for (auto e_i : boost::make_iterator_range(boost::edges(graph))) {
        auto edge = get_edge_id(e_i);
        int64_t color = graph[e_i];
        results.push_back({edge, (color + 1)});
    }
    return results;
}

Pgr_edgeColoring::Pgr_edgeColoring(pgr_edge_t *edges,
                                   size_t total_edges) {
    /*
     * Inserting vertices
     */
    Identifiers<int64_t> ids;
    for (size_t i = 0; i < total_edges; ++i) {
        ids += edges[i].source;
        ids += edges[i].target;
    }

    for (const auto id : ids) {
        auto v = add_vertex(graph);
        id_to_V.insert(std::make_pair(id, v));
        V_to_id.insert(std::make_pair(v, id));
    }

    /*
     * Inserting edges
     */
    bool added;
    for (size_t i = 0; i < total_edges; ++i) {
        auto edge = edges[i];
        auto v1 = get_boost_vertex(edge.source);
        auto v2 = get_boost_vertex(edge.target);
        auto e_exists = boost::edge(v1, v2, graph);
        if (e_exists.second) continue;

        if (edge.source == edge.target) continue;

        E e;
#if 1
        boost::tie(e, added) = boost::add_edge(v1, v2, edge.cost, graph);
#else
        boost::tie(e, added) = boost::add_edge(v1, v2, graph);
#endif

        E_to_id.insert(std::make_pair(e, edge.id));
    }
}

Pgr_edgeColoring::V
Pgr_edgeColoring::get_boost_vertex(int64_t id) const {
    try {
        return id_to_V.at(id);
    } catch (...) {
        pgassert(false);
        throw;
    }
}

int64_t
Pgr_edgeColoring::get_vertex_id(V v) const {
    try {
        return V_to_id.at(v);
    } catch (...) {
        pgassert(false);
        throw;
    }
}

int64_t
Pgr_edgeColoring::get_edge_id(E e) const {
    try {
        return E_to_id.at(e);
    } catch (...) {
        pgassert(false);
        throw;
    }
}

}  // namespace functions
}  // namespace pgrouting