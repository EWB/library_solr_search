<?php
/**
 * @file
 * library_solr_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function library_solr_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facetapi:block_cache:search_api@solr_index';
  $strongarm->value = -1;
  $export['facetapi:block_cache:search_api@solr_index'] = $strongarm;

  return $export;
}
