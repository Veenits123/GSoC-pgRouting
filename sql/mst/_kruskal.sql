/*PGR-GNU*****************************************************************
File: kruskal.sql

Generated with Template by:
Copyright (c) 2016 pgRouting developers
Mail: project@pgrouting.org

Function's developer:
Copyright (c) 2018 Aditya Pratap Singh
Mail: adityapratap.singh28@gmail.com

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

CREATE OR REPLACE FUNCTION _pgr_kruskal(
    TEXT,             -- Edge sql
    BIGINT,           -- tree root for traversal
    order_by TEXT,
    max_depth INTEGER,

    OUT seq INTEGER,
    OUT depth BIGINT,
    OUT node BIGINT,
    OUT edge BIGINT,
    OUT cost FLOAT,
    OUT agg_cost FLOAT)
RETURNS SETOF RECORD AS
'MODULE_PATHNAME', 'kruskal'
LANGUAGE C VOLATILE STRICT;
