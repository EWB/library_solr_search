<?php
/**
 * @file
 * library_solr_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function library_solr_search_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function library_solr_search_default_search_api_index() {
  $items = array();
  $items['solr_index'] = entity_import('search_api_index', '{
    "name" : "Solr Index",
    "machine_name" : "solr_index",
    "description" : null,
    "server" : "solr_server",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "200",
      "fields" : {
        "type" : { "type" : "string" },
        "title" : { "type" : "text" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_database_brief_description" : { "type" : "text" },
        "field_database_subject" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "search_api_language" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [  ] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [  ] },
        "search_api_alter_node_status" : { "status" : 0, "weight" : "0", "settings" : [  ] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [  ] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [  ] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [  ] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true, "field_database_brief_description" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : { "title" : true, "field_database_brief_description" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\u000D\\u000Ah2 = 3\\u000D\\u000Ah3 = 2\\u000D\\u000Astrong = 2\\u000D\\u000Ab = 2\\u000D\\u000Aem = 1.5\\u000D\\u000Au = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true, "field_database_brief_description" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true, "field_database_brief_description" : true },
            "file" : "",
            "stopwords" : "but\\u000D\\u000Adid\\u000D\\u000Athe this that those\\u000D\\u000Aetc"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "metatags" : [  ],
    "rdf_mapping" : [  ]
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_page().
 */
function library_solr_search_default_search_api_page() {
  $items = array();
  $items['library_solr_search'] = entity_import('search_api_page', '{
    "index_id" : "solr_index",
    "path" : "search",
    "name" : "Library Solr Search",
    "machine_name" : "library_solr_search",
    "description" : null,
    "options" : {
      "mode" : "terms",
      "fields" : [  ],
      "per_page" : "10",
      "get_per_page" : 1,
      "view_mode" : "search_api_page_result"
    },
    "enabled" : "1",
    "metatags" : [  ],
    "rdf_mapping" : [  ]
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function library_solr_search_default_search_api_server() {
  $items = array();
  $items['solr_server'] = entity_import('search_api_server', '{
    "name" : "Solr Server",
    "machine_name" : "solr_server",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\u002Fsolr",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0
    },
    "enabled" : "1",
    "metatags" : [  ],
    "rdf_mapping" : [  ]
  }');
  return $items;
}
